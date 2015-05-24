/*-
 * Copyright 2005 Colin Percival
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _SHA512_H_
#define _SHA512_H_

#include <sys/types.h>

typedef struct SHA512Context {
	uint64_t state[8];
	uint64_t count[2];
	unsigned char buf[128];
} SHA512_CTX;

__BEGIN_DECLS

/* Ensure libmd symbols do not clash with libcrypto */

#ifndef SHA512_Init
#define SHA512_Init		_libmd_SHA512_Init
#endif
#ifndef SHA512_Update
#define SHA512_Update		_libmd_SHA512_Update
#endif
#ifndef SHA512_Final
#define SHA512_Final		_libmd_SHA512_Final
#endif
#ifndef SHA512_End
#define SHA512_End		_libmd_SHA512_End
#endif
#ifndef SHA512_File
#define SHA512_File		_libmd_SHA512_File
#endif
#ifndef SHA512_FileChunk
#define SHA512_FileChunk	_libmd_SHA512_FileChunk
#endif
#ifndef SHA512_Data
#define SHA512_Data		_libmd_SHA512_Data
#endif

#ifndef SHA512_Transform
#define SHA512_Transform	_libmd_SHA512_Transform
#endif
#ifndef SHA512_version
#define SHA512_version		_libmd_SHA512_version
#endif

void	SHA512_Init(SHA512_CTX *);
void	SHA512_Update(SHA512_CTX *, const void *, size_t);
void	SHA512_Final(unsigned char [64], SHA512_CTX *);
char   *SHA512_End(SHA512_CTX *, char *);
char   *SHA512_File(const char *, char *);
char   *SHA512_FileChunk(const char *, char *, off_t, off_t);
char   *SHA512_Data(const void *, unsigned int, char *);
__END_DECLS

#endif /* !_SHA512_H_ */
