/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	@(#)sys_generic.c	8.3 (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/socketvar.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/stat.h>
#include <sys/malloc.h>
#ifdef KTRACE
#include <sys/ktrace.h>
#endif

/*
 * Read system call.
 */
struct read_args {
	int	fd;
	char	*buf;
	u_int	nbyte;
};
/* ARGSUSED */
read(p, uap, retval)
	struct proc *p;
	register struct read_args *uap;
	int *retval;
{
	register struct file *fp;
	register struct filedesc *fdp = p->p_fd;
	struct uio auio;
	struct iovec aiov;
	long cnt, error = 0;
#ifdef KTRACE
	struct iovec ktriov;
#endif

	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
	    (fp->f_flag & FREAD) == 0)
		return (EBADF);
	aiov.iov_base = (caddr_t)uap->buf;
	aiov.iov_len = uap->nbyte;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_resid = uap->nbyte;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_procp = p;
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
	if (KTRPOINT(p, KTR_GENIO))
		ktriov = aiov;
#endif
	cnt = uap->nbyte;
	if (error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred))
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
	cnt -= auio.uio_resid;
#ifdef KTRACE
	if (KTRPOINT(p, KTR_GENIO) && error == 0)
		ktrgenio(p->p_tracep, uap->fd, UIO_READ, &ktriov, cnt, error);
#endif
	*retval = cnt;
	return (error);
}

/*
 * Scatter read system call.
 */
struct readv_args {
	int	fdes;
	struct	iovec *iovp;
	u_int	iovcnt;
};
readv(p, uap, retval)
	struct proc *p;
	register struct readv_args *uap;
	int *retval;
{
	register struct file *fp;
	register struct filedesc *fdp = p->p_fd;
	struct uio auio;
	register struct iovec *iov;
	struct iovec *needfree;
	struct iovec aiov[UIO_SMALLIOV];
	long i, cnt, error = 0;
	u_int iovlen;
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif

	if (((u_int)uap->fdes) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL ||
	    (fp->f_flag & FREAD) == 0)
		return (EBADF);
	/* note: can't use iovlen until iovcnt is validated */
	iovlen = uap->iovcnt * sizeof (struct iovec);
	if (uap->iovcnt > UIO_SMALLIOV) {
		if (uap->iovcnt > UIO_MAXIOV)
			return (EINVAL);
		MALLOC(iov, struct iovec *, iovlen, M_IOV, M_WAITOK);
		needfree = iov;
	} else {
		iov = aiov;
		needfree = NULL;
	}
	auio.uio_iov = iov;
	auio.uio_iovcnt = uap->iovcnt;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_procp = p;
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov, iovlen))
		goto done;
	auio.uio_resid = 0;
	for (i = 0; i < uap->iovcnt; i++) {
		if (iov->iov_len < 0) {
			error = EINVAL;
			goto done;
		}
		auio.uio_resid += iov->iov_len;
		if (auio.uio_resid < 0) {
			error = EINVAL;
			goto done;
		}
		iov++;
	}
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
	if (KTRPOINT(p, KTR_GENIO))  {
		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
	}
#endif
	cnt = auio.uio_resid;
	if (error = (*fp->f_ops->fo_read)(fp, &auio, fp->f_cred))
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
	cnt -= auio.uio_resid;
#ifdef KTRACE
	if (ktriov != NULL) {
		if (error == 0)
			ktrgenio(p->p_tracep, uap->fdes, UIO_READ, ktriov,
			    cnt, error);
		FREE(ktriov, M_TEMP);
	}
#endif
	*retval = cnt;
done:
	if (needfree)
		FREE(needfree, M_IOV);
	return (error);
}

/*
 * Write system call
 */
struct write_args {
	int	fd;
	char	*buf;
	u_int	nbyte;
};
write(p, uap, retval)
	struct proc *p;
	register struct write_args *uap;
	int *retval;
{
	register struct file *fp;
	register struct filedesc *fdp = p->p_fd;
	struct uio auio;
	struct iovec aiov;
	long cnt, error = 0;
#ifdef KTRACE
	struct iovec ktriov;
#endif

	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
	    (fp->f_flag & FWRITE) == 0)
		return (EBADF);
	aiov.iov_base = (caddr_t)uap->buf;
	aiov.iov_len = uap->nbyte;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_resid = uap->nbyte;
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_procp = p;
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
	if (KTRPOINT(p, KTR_GENIO))
		ktriov = aiov;
#endif
	cnt = uap->nbyte;
	if (error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred)) {
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		if (error == EPIPE)
			psignal(p, SIGPIPE);
	}
	cnt -= auio.uio_resid;
#ifdef KTRACE
	if (KTRPOINT(p, KTR_GENIO) && error == 0)
		ktrgenio(p->p_tracep, uap->fd, UIO_WRITE,
		    &ktriov, cnt, error);
#endif
	*retval = cnt;
	return (error);
}

/*
 * Gather write system call
 */
struct writev_args {
	int	fd;
	struct	iovec *iovp;
	u_int	iovcnt;
};
writev(p, uap, retval)
	struct proc *p;
	register struct writev_args *uap;
	int *retval;
{
	register struct file *fp;
	register struct filedesc *fdp = p->p_fd;
	struct uio auio;
	register struct iovec *iov;
	struct iovec *needfree;
	struct iovec aiov[UIO_SMALLIOV];
	long i, cnt, error = 0;
	u_int iovlen;
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif

	if (((u_int)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL ||
	    (fp->f_flag & FWRITE) == 0)
		return (EBADF);
	/* note: can't use iovlen until iovcnt is validated */
	iovlen = uap->iovcnt * sizeof (struct iovec);
	if (uap->iovcnt > UIO_SMALLIOV) {
		if (uap->iovcnt > UIO_MAXIOV)
			return (EINVAL);
		MALLOC(iov, struct iovec *, iovlen, M_IOV, M_WAITOK);
		needfree = iov;
	} else {
		iov = aiov;
		needfree = NULL;
	}
	auio.uio_iov = iov;
	auio.uio_iovcnt = uap->iovcnt;
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_procp = p;
	if (error = copyin((caddr_t)uap->iovp, (caddr_t)iov, iovlen))
		goto done;
	auio.uio_resid = 0;
	for (i = 0; i < uap->iovcnt; i++) {
		if (iov->iov_len < 0) {
			error = EINVAL;
			goto done;
		}
		auio.uio_resid += iov->iov_len;
		if (auio.uio_resid < 0) {
			error = EINVAL;
			goto done;
		}
		iov++;
	}
#ifdef KTRACE
	/*
	 * if tracing, save a copy of iovec
	 */
	if (KTRPOINT(p, KTR_GENIO))  {
		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
	}
#endif
	cnt = auio.uio_resid;
	if (error = (*fp->f_ops->fo_write)(fp, &auio, fp->f_cred)) {
		if (auio.uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		if (error == EPIPE)
			psignal(p, SIGPIPE);
	}
	cnt -= auio.uio_resid;
#ifdef KTRACE
	if (ktriov != NULL) {
		if (error == 0)
			ktrgenio(p->p_tracep, uap->fd, UIO_WRITE,
				ktriov, cnt, error);
		FREE(ktriov, M_TEMP);
	}
#endif
	*retval = cnt;
done:
	if (needfree)
		FREE(needfree, M_IOV);
	return (error);
}

/*
 * Ioctl system call
 */
struct ioctl_args {
	int	fd;
	int	com;
	caddr_t	data;
};
/* ARGSUSED */
ioctl(p, uap, retval)
	struct proc *p;
	register struct ioctl_args *uap;
	int *retval;
{
	register struct file *fp;
	register struct filedesc *fdp;
	register int com, error;
	register u_int size;
	caddr_t data, memp;
	int tmp;
#define STK_PARAMS	128
	char stkbuf[STK_PARAMS];

	fdp = p->p_fd;
	if ((u_int)uap->fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
		return (EBADF);

	if ((fp->f_flag & (FREAD | FWRITE)) == 0)
		return (EBADF);

	switch (com = uap->com) {
	case FIONCLEX:
		fdp->fd_ofileflags[uap->fd] &= ~UF_EXCLOSE;
		return (0);
	case FIOCLEX:
		fdp->fd_ofileflags[uap->fd] |= UF_EXCLOSE;
		return (0);
	}

	/*
	 * Interpret high order word to find amount of data to be
	 * copied to/from the user's address space.
	 */
	size = IOCPARM_LEN(com);
	if (size > IOCPARM_MAX)
		return (ENOTTY);
	memp = NULL;
	if (size > sizeof (stkbuf)) {
		memp = (caddr_t)malloc((u_long)size, M_IOCTLOPS, M_WAITOK);
		data = memp;
	} else
		data = stkbuf;
	if (com&IOC_IN) {
		if (size) {
			error = copyin(uap->data, data, (u_int)size);
			if (error) {
				if (memp)
					free(memp, M_IOCTLOPS);
				return (error);
			}
		} else
			*(caddr_t *)data = uap->data;
	} else if ((com&IOC_OUT) && size)
		/*
		 * Zero the buffer so the user always
		 * gets back something deterministic.
		 */
		bzero(data, size);
	else if (com&IOC_VOID)
		*(caddr_t *)data = uap->data;

	switch (com) {

	case FIONBIO:
		if (tmp = *(int *)data)
			fp->f_flag |= FNONBLOCK;
		else
			fp->f_flag &= ~FNONBLOCK;
		error = (*fp->f_ops->fo_ioctl)(fp, FIONBIO, (caddr_t)&tmp, p);
		break;

	case FIOASYNC:
		if (tmp = *(int *)data)
			fp->f_flag |= FASYNC;
		else
			fp->f_flag &= ~FASYNC;
		error = (*fp->f_ops->fo_ioctl)(fp, FIOASYNC, (caddr_t)&tmp, p);
		break;

	case FIOSETOWN:
		tmp = *(int *)data;
		if (fp->f_type == DTYPE_SOCKET) {
			((struct socket *)fp->f_data)->so_pgid = tmp;
			error = 0;
			break;
		}
		if (tmp <= 0) {
			tmp = -tmp;
		} else {
			struct proc *p1 = pfind(tmp);
			if (p1 == 0) {
				error = ESRCH;
				break;
			}
			tmp = p1->p_pgrp->pg_id;
		}
		error = (*fp->f_ops->fo_ioctl)
			(fp, (int)TIOCSPGRP, (caddr_t)&tmp, p);
		break;

	case FIOGETOWN:
		if (fp->f_type == DTYPE_SOCKET) {
			error = 0;
			*(int *)data = ((struct socket *)fp->f_data)->so_pgid;
			break;
		}
		error = (*fp->f_ops->fo_ioctl)(fp, (int)TIOCGPGRP, data, p);
		*(int *)data = -*(int *)data;
		break;

	default:
		error = (*fp->f_ops->fo_ioctl)(fp, com, data, p);
		/*
		 * Copy any data to user, size was
		 * already set and checked above.
		 */
		if (error == 0 && (com&IOC_OUT) && size)
			error = copyout(data, uap->data, (u_int)size);
		break;
	}
	if (memp)
		free(memp, M_IOCTLOPS);
	return (error);
}

int	selwait, nselcoll;

/*
 * Select system call.
 */
struct select_args {
	u_int	nd;
	fd_set	*in, *ou, *ex;
	struct	timeval *tv;
};
select(p, uap, retval)
	register struct proc *p;
	register struct select_args *uap;
	int *retval;
{
	fd_set ibits[3], obits[3];
	struct timeval atv;
	int s, ncoll, error = 0, timo;
	u_int ni;

	bzero((caddr_t)ibits, sizeof(ibits));
	bzero((caddr_t)obits, sizeof(obits));
	if (uap->nd > FD_SETSIZE)
		return (EINVAL);
	if (uap->nd > p->p_fd->fd_nfiles)
		uap->nd = p->p_fd->fd_nfiles;	/* forgiving; slightly wrong */
	ni = howmany(uap->nd, NFDBITS) * sizeof(fd_mask);

#define	getbits(name, x) \
	if (uap->name && \
	    (error = copyin((caddr_t)uap->name, (caddr_t)&ibits[x], ni))) \
		goto done;
	getbits(in, 0);
	getbits(ou, 1);
	getbits(ex, 2);
#undef	getbits

	if (uap->tv) {
		error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
			sizeof (atv));
		if (error)
			goto done;
		if (itimerfix(&atv)) {
			error = EINVAL;
			goto done;
		}
		s = splclock();
		timevaladd(&atv, (struct timeval *)&time);
		timo = hzto(&atv);
		/*
		 * Avoid inadvertently sleeping forever.
		 */
		if (timo == 0)
			timo = 1;
		splx(s);
	} else
		timo = 0;
retry:
	ncoll = nselcoll;
	p->p_flag |= SSEL;
	error = selscan(p, ibits, obits, uap->nd, retval);
	if (error || *retval)
		goto done;
	s = splhigh();
	/* this should be timercmp(&time, &atv, >=) */
	if (uap->tv && (time.tv_sec > atv.tv_sec ||
	    time.tv_sec == atv.tv_sec && time.tv_usec >= atv.tv_usec)) {
		splx(s);
		goto done;
	}
	if ((p->p_flag & SSEL) == 0 || nselcoll != ncoll) {
		splx(s);
		goto retry;
	}
	p->p_flag &= ~SSEL;
	error = tsleep((caddr_t)&selwait, PSOCK | PCATCH, "select", timo);
	splx(s);
	if (error == 0)
		goto retry;
done:
	p->p_flag &= ~SSEL;
	/* select is not restarted after signals... */
	if (error == ERESTART)
		error = EINTR;
	if (error == EWOULDBLOCK)
		error = 0;
#define	putbits(name, x) \
	if (uap->name && \
	    (error2 = copyout((caddr_t)&obits[x], (caddr_t)uap->name, ni))) \
		error = error2;
	if (error == 0) {
		int error2;

		putbits(in, 0);
		putbits(ou, 1);
		putbits(ex, 2);
#undef putbits
	}
	return (error);
}

selscan(p, ibits, obits, nfd, retval)
	struct proc *p;
	fd_set *ibits, *obits;
	int nfd, *retval;
{
	register struct filedesc *fdp = p->p_fd;
	register int msk, i, j, fd;
	register fd_mask bits;
	struct file *fp;
	int n = 0;
	static int flag[3] = { FREAD, FWRITE, 0 };

	for (msk = 0; msk < 3; msk++) {
		for (i = 0; i < nfd; i += NFDBITS) {
			bits = ibits[msk].fds_bits[i/NFDBITS];
			while ((j = ffs(bits)) && (fd = i + --j) < nfd) {
				bits &= ~(1 << j);
				fp = fdp->fd_ofiles[fd];
				if (fp == NULL)
					return (EBADF);
				if ((*fp->f_ops->fo_select)(fp, flag[msk], p)) {
					FD_SET(fd, &obits[msk]);
					n++;
				}
			}
		}
	}
	*retval = n;
	return (0);
}

/*ARGSUSED*/
seltrue(dev, flag, p)
	dev_t dev;
	int flag;
	struct proc *p;
{

	return (1);
}

/*
 * Record a select request.
 */
void
selrecord(selector, sip)
	struct proc *selector;
	struct selinfo *sip;
{
	struct proc *p;
	pid_t mypid;

	mypid = selector->p_pid;
	if (sip->si_pid == mypid)
		return;
	if (sip->si_pid && (p = pfind(sip->si_pid)) &&
	    p->p_wchan == (caddr_t)&selwait)
		sip->si_flags |= SI_COLL;
	else
		sip->si_pid = mypid;
}

/*
 * Do a wakeup when a selectable event occurs.
 */
void
selwakeup(sip)
	register struct selinfo *sip;
{
	register struct proc *p;
	int s;

	if (sip->si_pid == 0)
		return;
	if (sip->si_flags & SI_COLL) {
		nselcoll++;
		sip->si_flags &= ~SI_COLL;
		wakeup((caddr_t)&selwait);
	}
	p = pfind(sip->si_pid);
	sip->si_pid = 0;
	if (p != NULL) {
		s = splhigh();
		if (p->p_wchan == (caddr_t)&selwait) {
			if (p->p_stat == SSLEEP)
				setrunnable(p);
			else
				unsleep(p);
		} else if (p->p_flag & SSEL)
			p->p_flag &= ~SSEL;
		splx(s);
	}
}
