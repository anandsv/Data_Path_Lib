/****************************************************************************
Copyright (c) 2014, RapidIO Trade Association
Copyright (c) 2014, Indian Institute of Technology
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************/


#ifndef __RDMA_DEFS_H__
#define __RDMA_DEFS_H__

#include <RDMA_types.h>
// #include <linux/time.h>
typedef struct {
	unsigned int tv_sec;
	unsigned int tv_nsec;
} timespec;

const extern timespec FOREVER;

/********** Utility  functions **********************/

/*
* Returns pointer to local memory space, along with the size of the memory
* space in bytes.
*/
STATUS get_info_from_ms_h(ms_h *msh, sec_key *sk, void **addr, UINT32 *size);


/********** Interface  functions **********************/

/*
* Get memory space owner
*
* Input: Name of the memory space owner.
* Input: Security key value associated with the memory space owner.
* Output: a unique handle which is used to group ownership of memory spaces.
*/
STATUS get_mso_h(char *owner_name, sec_key *sk, mso_h *mso);


/*
* Returns a memory space identifier, and a pointer to memory that can be
* used by the thread/process to read/write to that memory (*mp).
*
* Input: mso, sk, bytes, flags, *m, *mp
* Output: *m updated to point to new memory space handle
* Output: *mp updated to point to first byte of the new local memory space
*/
STATUS get_ms(mso_h *mso, sec_key *sk, UINT32 bytes, UINT32 flags, ms **m,
								void **mp);


/*
* Request for a memory space handle for a subset of a memory space, as defined
* by the offset from the starting address of the memory space, and the number
* of bytes. Returns an ms_h that can be used to create further ms_h’s for
* subsections of the memory, and a pointer to the memory space handle that
* can be used to access that  memory space (*msh).

* Input: ms, sk, offset, bytes, *ms, *msu, flags
* Output: *msh updated to point to a new memory space handle
* Output: *mp updated to point to the first byte of the new memory space handle.
*/
STATUS get_ms_h(ms *m, sec_key *sk, UINT32 offset,
	UINT32 bytes, UINT32 flags, ms_h **msh, void **mp);


/*
* Enables access from the RapidIO fabric to all the physical memory identified
* by the * msu. Other nodes can now connect to the memory identified by the
* msu
* Input: msh, sk
*/
STATUS register_ms_h(ms_h *msh, sec_key *sk);


/*
* Requests that this process/thread be given access to the memory space
* identified by  the ms_h.
* Note that the memory space can be local (on the same processor) or remote
* (access  over RapidIO).
* The memory space must be registered if it does not exist on the local
* processor.
* NOTE: conn_ms_h may make multiple attempts to connect during the timeout
* period, to overcome synchronization issues between registering a memory space
* and  connecting to it.
* Input: msu, sk
*/
STATUS conn_ms_h(ms_h *msh, sec_key *sk, timespec timeout);


/*
* Requests that this process/thread, as identified by the security key,
* should no longer  have access to the memory space identified by the ms_h.
*/
STATUS disc_ms_h(ms_h *msh, sec_key *sk);


/*
* Inputs: in_parms. The in_parms structure contains the following:
*         — ms_h *loc_msh
*         — loc_offset within *loc_msh
*         — num_bytes
*         — ms_h *rem_msh
*         — rem_offset within *rem_msh
*         — priority: Absolute RapidIO priority of this transfer,
*                                                    priority value + CRF
*         — sync_type: enumerated type with options of
*         – no_wait: push_ms returns immediately, DMA transfer completion
*                    cannot be  checked
*         – async_chk: push_ms returns immediately, request handle to
*                      check for completion.
*         – sync_chk: push_ms returns when the DMA transfer has completed
*         — sec_key *sk
* Outputs: out_parms. The out_parms structure contains the following:
*         — Success/failure of input parameter checking
*         — Success/failure of DMA transfer (if req_chk == sync_chk)
*         — chk_handle: Handle to use in call to sync_chk_push_pull to test
*           for completion  of this transfer.
* Requests that the transfer of ‘num_bytes’ of memory space starting at
* “loc_offset” * from the beginning of the local memory space indicated by
* “loc_msu”, to  “rem_offset” from the start of the remote memory
* identified by “rem_msu”.The requesting software must have called
* conn_ms_h sucessfully before this call.
*/
STATUS push_ms(struct xfer_ms_in *in_parms, struct xfer_ms_out *out_parms);


/*
* Note: parameters are identical to push_ms.
* Requests that the transfer of ‘num_bytes’ of memory space starting at
* “rem_offset”  from the start of the remote memory identified by
* "rem_msu" to offset “loc_offset”  from the beginning of the local
* memory space identified by “loc_msu”.
*/
STATUS pull_ms(struct xfer_ms_in *in_parms, struct xfer_ms_out *out_parms);


/*
* Synchronizes application to completion of a push or pull operation
* associated with  the chk_handle.
* If *wait specifies 0 seconds 0 nanoseconds, sync_chk_push_pull returns
* immediately if the chk_handle has not been completed.
* Otherwise, sync_chk_push_pull returns when there is a timeout or when
* the transfer  has completed.
* Note: completion of a transfer could be unsuccessful.
*/
STATUS sync_chk_push_pull(ms_h *loc_msh, sec_key *sk,
					chk_handle *chk, timespec *wait);


/*
* Disables external access to all the physical memory identified by the msh
*/
STATUS deregister_ms_h(ms_h *msh, sec_key *sk);


/*
* Requests that the memory space owned by “mso” and identified by “m”
* should  be  returned to the RDMA memory pool.
*/
STATUS drop_ms(mso_h *mso, ms *m, sec_key *sk);


/*
* Frees up the memory space owner handle. The memory space owner handle may be
* re-used immediately by new memory space owners.
*/
STATUS drop_mso_h(mso_h *mso, sec_key *sk);

#endif /* __RDMA_DEFS_H__ */
