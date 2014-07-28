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


#ifndef __RDMA_TYPES_H__
#define __RDMA_TYPES_H__

typedef unsigned int UINT32;


/*
* UINT32 flags - bit vector of attributes/control values, to be refined/revised
* as implementation progresses and user requirements become more clear.
* presumed defined in system types file - To be checked - madhu
*/

/*
* mso_h - A memory space owner handle. This is a globally unique value within
* the RDMA system. User software must be designed to return all memory spaces
* owned by this handle to the RDMA system if the owner process terminates or
* no longer needs the memory space.
*/
typedef UINT32 mso_h;

/*
* ms - memory space identifier. This is a globally unique identifier within
* the RDMA system. It identifies a memory space within the RDMA system. A
* memory space is identified by a starting virtual address and a number of
* bytes. The memory space can be treated by the application as if it was
* contiguous, even if physically the memory is not contiguous.
*/
typedef UINT32 ms;

/*
* ms_h - memory space handle. This is a globally unique identifier within
* the RDMA system. It identifies a subspace within a memory space within the
* RDMA system.
*/
typedef UINT32 ms_h;

/*
* sec_key - security key value used for authentication and validation of
* access to an ms and  ms_h. The mechanisms for managing and validating
* sec_keys will be refined in a future specification revision. sec_key types
* are not supported as part of this revision of the
* specification.
*/
typedef UINT32 sec_key;

typedef int STATUS;

/*
* typdef for synchronization type
*/
typedef enum  {no_wait, async_chk, sync_chk} sync_type_t;

typedef void (*chk_handle)();

struct xfer_ms_in {
	ms_h *loc_msh;
	int loc_offset;
	int num_bytes;
	ms_h *rem_msh;
	int rem_offset;
	int priority;
	sync_type_t sync_types;
	sec_key *sk;
};

struct xfer_ms_out {
	STATUS in_param_ok;
	STATUS dma_xfr_status;
	chk_handle completion_handle;
};

#endif /* __RDMA_TYPES_H__ */
