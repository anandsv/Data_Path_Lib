
/****************************************************************************
Copyright (c) 2014, RapidIO Trade Association
Copyright (c) 2014, Integrated Device Technology, Inc.
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

#include <stdlib.h>
#include <stdio.h>
#include "RDMA_defs.h"

const timespec FOREVER = {0xFFFFFFFF, 0xFFFFFFFF};

STATUS get_info_from_ms_h(ms_h *msh, sec_key *sk, void **addr, UINT32 *size)
{
	sk = NULL;
	*addr = NULL;
	*size = 0;
	return 0;
};


STATUS get_mso_h(char *owner_name, sec_key *sk, mso_h *mso) 
{
	printf("get_mso_h: Owner_name \"%s\"", owner_name);
	sk = NULL;
	mso = NULL;
	
	return 0;

};

STATUS get_ms(mso_h *mso, sec_key *sk, UINT32 bytes, UINT32 flags, ms **m,
								void **mp)
{
	printf("get_ms: mso_h 0x%x sec_key 0x%0x\n", mso, sk);
	printf("        bytes 0x%x flags   0x%0x\n", bytes, flags);
	*m = NULL;
	*mp = NULL;

	return 0;
};


STATUS get_ms_h(ms *m, sec_key *sk, UINT32 offset,
	UINT32 bytes, UINT32 flags, ms_h **msh, void **mp)
{
	printf("get_ms_h: m 0x%x sec_key 0x%0x\n", m, sk);
	printf("        offset 0x%x bytes 0x%0x flags   0x%0x\n", 
		offset, bytes, flags);
	*msh = NULL;
	*mp = NULL;

	return 0;
};


STATUS register_ms_h(ms_h *msh, sec_key *sk)
{
	printf("register_ms_h: msh 0x%x sk 0x%0x\n", msh, sk);

	return 0;
};


STATUS conn_ms_h(ms_h *msh, sec_key *sk, timespec timeout)
{
	printf("conn_ms_h: msh 0x%x sk 0x%0x\n time s %d ns %d", msh, sk,
		timeout.tv_sec, timeout.tv_nsec);

	return 0;
};


STATUS disc_ms_h(ms_h *msh, sec_key *sk)
{
	printf("disc_ms_h: msh 0x%x sk 0x%0x\n", msh, sk);

	return 0;
};


STATUS push_ms(struct xfer_ms_in *in_parms, struct xfer_ms_out *out_parms)
{
	printf("push_ms: in_parms 0x%x out_parms 0x%0x\n", in_parms, out_parms);

	return 0;
};


STATUS pull_ms(struct xfer_ms_in *in_parms, struct xfer_ms_out *out_parms)
{
	printf("pull_ms: in_parms 0x%x out_parms 0x%0x\n", in_parms, out_parms);

	return 0;
};


STATUS sync_chk_push_pull(ms_h *loc_msh, sec_key *sk,
					chk_handle *chk, timespec *wait)
{
	printf("sync_chk_push_pull: loc_msh 0x%x sk 0x%x chk 0x%x",
		loc_msh, sk, chk);
	printf("                    time s %d ns %d", 
		wait->tv_sec, wait->tv_nsec);

	return 0;
};


/*
* Disables external access to all the physical memory identified by the msh
*/
STATUS deregister_ms_h(ms_h *msh, sec_key *sk)
{
	printf("deregister_ms_h: msh 0x%x sk 0x%x", msh, sk );

	return 0;
};


/*
* Requests that the memory space owned by “mso” and identified by “m”
* should  be  returned to the RDMA memory pool.
*/
STATUS drop_ms(mso_h *mso, ms *m, sec_key *sk)
{
	printf("drop_ms: mso 0x%x m 0x%x sk 0x%x", mso, m, sk );

	return 0;
};


STATUS drop_mso_h(mso_h *mso, sec_key *sk)
{
	printf("drop_mso_h: mso 0x%x sk 0x%x", mso, sk );

	return 0;
};

