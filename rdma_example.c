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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include "RDMA_types.h"
#include "RDMA_defs.h"

int main( int argc, char *argv[] )
{
	STATUS rc;
	mso_h mso;
	sec_key sk;
	ms   *ms_p;
	void *m_p;
	ms_h *msh_p;
	void *msh_mp;
	int pid;
	int child_status;
	timespec dlay = {0, 0};

	rc = get_mso_h("Demo", &sk,  &mso);

	printf("\nget_mso_h rc = 0x%x\n", rc );

	rc = get_ms( &mso, &sk, 10000, 0, &ms_p, &m_p );

	printf("\nget_ms rc = 0x%x\n", rc );
	printf("ms_p = 0x%x\n", ms_p);
	printf("mp = 0x%x\n", m_p);

	rc = get_ms_h( ms_p, &sk, 0, 4000, 0, &msh_p, &msh_mp );

	printf("\nget_ms_h rc = 0x%x\n", rc );
	printf("*msh_p  = 0x%x\n", msh_p);
	printf("*msh_mp = 0x%x\n", msh_mp);
	
	pid = fork();
	
	if (pid) {
		printf("\nParent pid 0x%x executing...\n", getpid());

		rc = conn_ms_h(msh_p, &sk, FOREVER);
		
	        printf("\nconn_ms_h Parent rc = 0x%x\n", rc );
		printf("\nParent pid 0x%x waiting...\n", getpid());
		wait(&child_status);
	} else {
		pid = getpid();
		printf("\nChild pid 0x%x executing...\n", pid);
		rc = conn_ms_h(msh_p, &sk, dlay);
		
	        printf("\nconn_ms_h Child rc = 0x%x\n", rc );
	
		rc = disc_ms_h(msh_p, &sk);
		
	        printf("\ndisc_ms_h Child rc = 0x%x\n", rc );
		exit(EXIT_SUCCESS);
	};

	rc = deregister_ms_h(ms_p, &sk);
	printf("\nderegister_ms_h rc = 0x%x\n", rc );

	rc = drop_ms(&mso, ms_p, &sk);
	printf("\ndrop_ms rc = 0x%x\n", rc );

	rc = drop_mso_h(&mso, &sk);
	printf("\ndrop_mso_h rc = 0x%x\n", rc );

	return 0;
};

