

void * _sbrk(ptrdiff_t __incr)
{
    return 0;
}

_READ_WRITE_RETURN_TYPE _write(int __fd, const void *__buf, size_t __nbyte)
{
    return 0;
}

int _close(int _fildes)
{
    return 0;
}

int _isatty(int _fildes)
{
    return 0;
}

_off_t _lseek(int _fildes, _off_t _offest, int _whence)
{
    return 0;
}

_READ_WRITE_RETURN_TYPE _read(int __fd, void *__buf, size_t _nbyte)
{
    return 0;
}

int _fstat(int __fd, struct stat *_sbuf)
{
    return 0;
}