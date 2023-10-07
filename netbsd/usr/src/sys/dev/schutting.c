#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/device.h>
#include <sys/conf.h>
#include <uvm/uvm_extern.h>

// Stub for autoconf(9)
// schuttingattach() needs to be spelled like this to prevent the linker from being sad
void schuttingattach(int num);

// File operations
int schutting_open(dev_t dev, int flags, int fmt, struct lwp *process);
int schutting_close(dev_t dev, int flags, int fmt, struct lwp *process);
int schutting_write(dev_t dev, struct uio *uio, int ioflag);
int schutting_read(dev_t dev, struct uio *uio, int ioflag);

// More macro fun from autoconf(9)
dev_type_open(schutting_open);
dev_type_close(schutting_close);
dev_type_write(schutting_write);
dev_type_read(schutting_read);

// Device switch table
const struct cdevsw schutting_cdevsw = {
    .d_open = schutting_open,
    .d_close = schutting_close,
    .d_read = schutting_read,
    .d_write = schutting_write,
    .d_ioctl = noioctl,
    .d_stop = nostop,
    .d_tty = notty,
    .d_poll = nopoll,
    .d_mmap = nommap,
    .d_kqfilter = nokqfilter,
    .d_discard = nodiscard,
    .d_flag = D_OTHER,
};

// Initialization function, don't really care about this
void schuttingattach(int num)
{
    printf("Attached schutting\n");
    return;
}

// Open function, does nothing
int schutting_open(dev_t dev, int flags, int fmt, struct lwp *process)
{
    return 0;
}

// Close function, same as open
int schutting_close(dev_t dev, int flags, int fmt, struct lwp *process)
{
    return 0;
}

// Read function, again does nothing
int schutting_read(dev_t dev, struct uio *uio, int ioflag)
{
    return 0;
}

// Write function, does something
int schutting_write(dev_t dev, struct uio *uio, int ioflag)
{
	int ret = uio->uio_resid;
	if (uio->uio_rw == UIO_WRITE)
	{
		uio->uio_resid = 0;
	}
	return ret;
}
