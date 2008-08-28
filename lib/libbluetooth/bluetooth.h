/*
 * bluetooth.h
 *
 * Copyright (c) 2001-2003 Maksim Yevmenkin <m_evmenkin@yahoo.com>
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
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: bluetooth.h,v 1.5 2003/09/14 23:28:42 max Exp $
 * $FreeBSD$
 */

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <sys/types.h>
#include <sys/bitstring.h>
#include <sys/endian.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netgraph/bluetooth/include/ng_hci.h>
#include <netgraph/bluetooth/include/ng_l2cap.h>
#include <netgraph/bluetooth/include/ng_btsocket.h>

__BEGIN_DECLS

/*
 * Linux BlueZ compatibility
 */

#define	bacmp(ba1, ba2)	memcmp((ba1), (ba2), sizeof(bdaddr_t))
#define	bacpy(dst, src)	memcpy((dst), (src), sizeof(bdaddr_t))
#define ba2str(ba, str)	bt_ntoa((ba), (str))
#define str2ba(str, ba)	(bt_aton((str), (ba)) == 1? 0 : -1)

/*
 * Interface to the outside world
 */

struct hostent *  bt_gethostbyname    (char const *name);
struct hostent *  bt_gethostbyaddr    (char const *addr, int len, int type);
struct hostent *  bt_gethostent       (void);
void              bt_sethostent       (int stayopen);
void              bt_endhostent       (void);

struct protoent * bt_getprotobyname   (char const *name);
struct protoent * bt_getprotobynumber (int proto);
struct protoent * bt_getprotoent      (void);
void              bt_setprotoent      (int stayopen);
void              bt_endprotoent      (void);

char const *      bt_ntoa             (bdaddr_t const *ba, char *str);
int               bt_aton             (char const *str, bdaddr_t *ba);

/*
 * bdaddr utility functions (from NetBSD)
 */

static __inline int
bdaddr_same(const bdaddr_t *a, const bdaddr_t *b)
{
	return (a->b[0] == b->b[0] && a->b[1] == b->b[1] &&
		a->b[2] == b->b[2] && a->b[3] == b->b[3] &&
		a->b[4] == b->b[4] && a->b[5] == b->b[5]);
}

static __inline int
bdaddr_any(const bdaddr_t *a)
{
	return (a->b[0] == 0 && a->b[1] == 0 && a->b[2] == 0 &&
		a->b[3] == 0 && a->b[4] == 0 && a->b[5] == 0);
}

static __inline void
bdaddr_copy(bdaddr_t *d, const bdaddr_t *s)
{
	d->b[0] = s->b[0];
	d->b[1] = s->b[1];
	d->b[2] = s->b[2];
	d->b[3] = s->b[3];
	d->b[4] = s->b[4];
	d->b[5] = s->b[5];
}

__END_DECLS

#endif /* ndef _BLUETOOTH_H_ */

