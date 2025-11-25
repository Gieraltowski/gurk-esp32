CREATE 0x0001 // R8=entry_point, R9=priority
TERMINATE 0x0002 // R8=pid
GETPID 0x0003 // (no args)
YIELD 0x0004 // (no args)
SLEEP 0x0005 // R8=milliseconds

MALLOC 0x0010 // R8=size
FREE 0x0011 // R8=pointer
REALLOC 0x0012 // R8=ptr, R9=new_size
CALLOC 0x0013 // R8=num, R9=size
MPROTECT 0x0014 // R8=addr, R9=len, R10=prot
MMAP 0x0015 // R8=addr, R9=length, R10=prot, R11=flags
MUNMAP 0x0016 // R8=addr, R9=length

MSGSEND 0x0020 // R8=queue_id, R9=msg_ptr, R10=size
MSGRECV 0x0021 // R8=queue_id, R9=buffer, R10=size
MSGCREATE 0x0022 // R8=max_msgs, R9=msg_size
MSGDELETE 0x0023 // R8=queue_id
SEMCREATE 0x0024 // R8=initial_count
SEMWAIT 0x0025 // R8=sem_id, R9=timeout
SEMPOST 0x0026 // R8=sem_id
SEMDELETE 0x0027 // R8=sem_id
MUTEXCREATE 0x0028 // (no args)
MUTEXLOCK 0x0029 // R8=mutex_id
MUTEXUNLOCK 0x002A // R8=mutex_id
MUTEXDELETE 0x002B // R8=mutex_id

OPEN 0x0030 // R8=path_ptr, R9=flags
CLOSE 0x0031 // R8=fd
READ 0x0032 // R8=fd, R9=buffer, R10=count
WRITE 0x0033 // R8=fd, R9=buffer, R10=count
SEEK 0x0034 // R8=fd, R9=offset, R10=whence
MKDIR 0x0035 // R8=path_ptr
RMDIR 0x0036 // R8=path_ptr
LISTDIR 0x0037 // R8=path_ptr, R9=buffer, R10=buf_size
FORMAT 0x0038 // (no args)
FSINFO 0x0039 // R8=info_struct_ptr

GPIOSETDIR 0x0040 // R8=pin, R9=direction
GPIOSETLVL 0x0041 // R8=pin, R9=level
GPIOGETLVL 0x0042 // R8=pin
I2CINIT 0x0043 // R8=bus, R9=sda_pin, R10=sclk_pin, R11=freq
I2CWRITE 0x0044 // R8=bus, R9=addr, R10=data_ptr, R11=len
I2CREAD 0x0045 // R8=bus, R9=addr, R10=data_ptr, R11=len
SPIINIT 0x0046 // R8=bus, R9=mosi_pin, R10=miso_pin, R11=sclk_pin, R12=freq
SPITRANSFER 0x0047 // R8=bus, R9=tx_data, R10=rx_data, R11=len
UARTINIT 0x0048 // R8=baud_rate, R9=tx_pin, R10=rx_pin
UARTWRITE 0x0049 // R8=data_ptr, R9=len
UARTREAD 0x004A // R8=buffer, R9=len
