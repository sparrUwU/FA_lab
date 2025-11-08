#include "error_list.h"

const char *linux_errlist[] = {
    "Success",                                      // 0
    "Operation not permitted",                      // EPERM
    "No such file or directory",                    // ENOENT  
    "No such process",                              // ESRCH
    "Interrupted system call",                      // EINTR
    "Input/output error",                           // EIO
    "No such device or address",                    // ENXIO
    "Argument list too long",                       // E2BIG
    "Exec format error",                            // ENOEXEC
    "Bad file descriptor",                          // EBADF
    "No child processes",                           // ECHILD
    "Resource temporarily unavailable",             // EAGAIN
    "Cannot allocate memory",                       // ENOMEM
    "Permission denied",                            // EACCES
    "Bad address",                                  // EFAULT
    "Block device required",                        // ENOTBLK
    "Device or resource busy",                      // EBUSY
    "File exists",                                  // EEXIST
    "Invalid cross-device link",                    // EXDEV
    "No such device",                               // ENODEV
    "Not a directory",                              // ENOTDIR
    "Is a directory",                               // EISDIR
    "Invalid argument",                             // EINVAL
    "Too many open files in system",                // ENFILE
    "Too many open files",                          // EMFILE
    "Inappropriate ioctl for device",               // ENOTTY
    "Text file busy",                               // ETXTBSY
    "File too large",                               // EFBIG
    "No space left on device",                      // ENOSPC
    "Illegal seek",                                 // ESPIPE
    "Read-only file system",                        // EROFS
    "Too many links",                               // EMLINK
    "Broken pipe",                                  // EPIPE
    "Numerical argument out of domain",             // EDOM
    "Numerical result out of range",                // ERANGE
    "Resource deadlock avoided",                    // EDEADLK
    "File name too long",                           // ENAMETOOLONG
    "No locks available",                           // ENOLCK
    "Function not implemented",                     // ENOSYS
    "Directory not empty",                          // ENOTEMPTY
    "Too many levels of symbolic links",            // ELOOP
    "Operation would block",                        // EWOULDBLOCK
    "No message of desired type",                   // ENOMSG
    "Identifier removed",                           // EIDRM
    "Channel number out of range",                  // ECHRNG
    "Level 2 not synchronized",                     // EL2NSYNC
    "Level 3 halted",                               // EL3HLT
    "Level 3 reset",                                // EL3RST
    "Link number out of range",                     // ELNRNG
    "Protocol driver not attached",                 // EUNATCH
    "No CSI structure available",                   // ENOCSI
    "Level 2 halted",                               // EL2HLT
    "Invalid exchange",                             // EBADE
    "Invalid request descriptor",                   // EBADR
    "Exchange full",                                // EXFULL
    "No anode",                                     // ENOANO
    "Invalid request code",                         // EBADRQC
    "Invalid slot",                                 // EBADSLT
    "Resource deadlock avoided",                    // EDEADLOCK
    "Bad font file format",                         // EBFONT
    "Device not a stream",                          // ENOSTR
    "No data available",                            // ENODATA
    "Timer expired",                                // ETIME
    "Out of streams resources",                     // ENOSR
    "Machine is not on the network",                // ENONET
    "Package not installed",                        // ENOPKG
    "Object is remote",                             // EREMOTE
    "Link has been severed",                        // ENOLINK
    "Advertise error",                              // EADV
    "Srmount error",                                // ESRMNT
    "Communication error on send",                  // ECOMM
    "Protocol error",                               // EPROTO
    "Multihop attempted",                           // EMULTIHOP
    "RFS specific error",                           // EDOTDOT
    "Bad message",                                  // EBADMSG
    "Value too large for defined data type",        // EOVERFLOW
    "Name not unique on network",                   // ENOTUNIQ
    "File descriptor in bad state",                 // EBADFD
    "Remote address changed",                       // EREMCHG
    "Can not access a needed shared library",       // ELIBACC
    "Accessing a corrupted shared library",         // ELIBBAD
    ".lib section in a.out corrupted",              // ELIBSCN
    "Attempting to link in too many shared libraries", // ELIBMAX
    "Cannot exec a shared library directly",        // ELIBEXEC
    "Invalid or incomplete multibyte or wide character", // EILSEQ
    "Interrupted system call should be restarted",  // ERESTART
    "Streams pipe error",                           // ESTRPIPE
    "Too many users",                               // EUSERS
    "Socket operation on non-socket",               // ENOTSOCK
    "Destination address required",                 // EDESTADDRREQ
    "Message too long",                             // EMSGSIZE
    "Protocol wrong type for socket",               // EPROTOTYPE
    "Protocol not available",                       // ENOPROTOOPT
    "Protocol not supported",                       // EPROTONOSUPPORT
    "Socket type not supported",                    // ESOCKTNOSUPPORT
    "Operation not supported",                      // EOPNOTSUPP
    "Protocol family not supported",                // EPFNOSUPPORT
    "Address family not supported by protocol",     // EAFNOSUPPORT
    "Address already in use",                       // EADDRINUSE
    "Cannot assign requested address",              // EADDRNOTAVAIL
    "Network is down",                              // ENETDOWN
    "Network is unreachable",                       // ENETUNREACH
    "Network dropped connection on reset",          // ENETRESET
    "Software caused connection abort",             // ECONNABORTED
    "Connection reset by peer",                     // ECONNRESET
    "No buffer space available",                    // ENOBUFS
    "Transport endpoint is already connected",      // EISCONN
    "Transport endpoint is not connected",          // ENOTCONN
    "Cannot send after transport endpoint shutdown", // ESHUTDOWN
    "Too many references: cannot splice",           // ETOOMANYREFS
    "Connection timed out",                         // ETIMEDOUT
    "Connection refused",                           // ECONNREFUSED
    "Host is down",                                 // EHOSTDOWN
    "No route to host",                             // EHOSTUNREACH
    "Operation already in progress",                // EALREADY
    "Operation now in progress",                    // EINPROGRESS
    "Stale file handle",                            // ESTALE
    "Structure needs cleaning",                     // EUCLEAN
    "Not a XENIX named type file",                  // ENOTNAM
    "No XENIX semaphores available",                // ENAVAIL
    "Is a named type file",                         // EISNAM
    "Remote I/O error",                             // EREMOTEIO
    "Disk quota exceeded",                          // EDQUOT
    "No medium found",                              // ENOMEDIUM
    "Wrong medium type",                            // EMEDIUMTYPE
    "Operation canceled",                           // ECANCELED
    "Required key not available",                   // ENOKEY
    "Key has expired",                              // EKEYEXPIRED
    "Key has been revoked",                         // EKEYREVOKED
    "Key was rejected by service",                  // EKEYREJECTED
    "Owner died",                                   // EOWNERDEAD
    "State not recoverable",                        // ENOTRECOVERABLE
    "Operation not possible due to RF-kill",        // ERFKILL
    "Memory page has hardware error"                // EHWPOISON
};

const int l_num_errors = sizeof(linux_errlist) / sizeof(linux_errlist[0]);


// MAC
const char *mac_errlist[] = {
    "Undefined error: 0",                         // 0
    "Operation not permitted",                    // EPERM
    "No such file or directory",                  // ENOENT
    "No such process",                            // ESRCH
    "Interrupted system call",                    // EINTR
    "Input/output error",                         // EIO
    "Device not configured",                      // ENXIO
    "Argument list too long",                     // E2BIG
    "Exec format error",                          // ENOEXEC
    "Bad file descriptor",                        // EBADF
    "No child processes",                         // ECHILD
    "Resource deadlock avoided",                  // EDEADLK
    "Cannot allocate memory",                     // ENOMEM
    "Permission denied",                          // EACCES
    "Bad address",                                // EFAULT
    "Block device required",                      // ENOTBLK
    "Resource busy",                              // EBUSY
    "File exists",                                // EEXIST
    "Cross-device link",                          // EXDEV
    "Operation not supported by device",          // ENODEV
    "Not a directory",                            // ENOTDIR
    "Is a directory",                             // EISDIR
    "Invalid argument",                           // EINVAL
    "Too many open files in system",              // ENFILE
    "Too many open files",                        // EMFILE
    "Inappropriate ioctl for device",             // ENOTTY
    "Text file busy",                             // ETXTBSY
    "File too large",                             // EFBIG
    "No space left on device",                    // ENOSPC
    "Illegal seek",                               // ESPIPE
    "Read-only file system",                      // EROFS
    "Too many links",                             // EMLINK
    "Broken pipe",                                // EPIPE
    "Numerical argument out of domain",           // EDOM
    "Result too large",                           // ERANGE
    "Resource temporarily unavailable",           // EAGAIN
    "Operation would block",                      // EWOULDBLOCK
    "Operation now in progress",                  // EINPROGRESS
    "Operation already in progress",              // EALREADY
    "Socket operation on non-socket",             // ENOTSOCK
    "Destination address required",               // EDESTADDRREQ
    "Message too long",                           // EMSGSIZE
    "Protocol wrong type for socket",             // EPROTOTYPE
    "Protocol not available",                     // ENOPROTOOPT
    "Protocol not supported",                     // EPROTONOSUPPORT
    "Socket type not supported",                  // ESOCKTNOSUPPORT
    "Operation not supported",                    // ENOTSUP
    "Protocol family not supported",              // EPFNOSUPPORT
    "Address family not supported by protocol",   // EAFNOSUPPORT
    "Address already in use",                     // EADDRINUSE
    "Can't assign requested address",             // EADDRNOTAVAIL
    "Network is down",                            // ENETDOWN
    "Network is unreachable",                     // ENETUNREACH
    "Network dropped connection on reset",        // ENETRESET
    "Software caused connection abort",           // ECONNABORTED
    "Connection reset by peer",                   // ECONNRESET
    "No buffer space available",                  // ENOBUFS
    "Socket is already connected",                // EISCONN
    "Socket is not connected",                    // ENOTCONN
    "Can't send after socket shutdown",           // ESHUTDOWN
    "Too many references: can't splice",          // ETOOMANYREFS
    "Operation timed out",                        // ETIMEDOUT
    "Connection refused",                         // ECONNREFUSED
    "Too many levels of symbolic links",          // ELOOP
    "File name too long",                         // ENAMETOOLONG
    "Host is down",                               // EHOSTDOWN
    "No route to host",                           // EHOSTUNREACH
    "Directory not empty",                        // ENOTEMPTY
    "Too many processes",                         // EPROCLIM
    "Too many users",                             // EUSERS
    "Disc quota exceeded",                        // EDQUOT
    "Stale NFS file handle",                      // ESTALE
    "Too many levels of remote in path",          // EREMOTE
    "RPC struct is bad",                          // EBADRPC
    "RPC version wrong",                          // ERPCMISMATCH
    "RPC prog. not avail",                        // EPROGUNAVAIL
    "Program version wrong",                      // EPROGMISMATCH
    "Bad procedure for program",                  // EPROCUNAVAIL
    "No locks available",                         // ENOLCK
    "Function not implemented",                   // ENOSYS
    "Inappropriate file type or format",          // EFTYPE
    "Authentication error",                       // EAUTH
    "Need authenticator",                         // ENEEDAUTH
    "Device power is off",                        // EPWROFF
    "Device error",                               // EDEVERR
    "Value too large to be stored in data type",  // EOVERFLOW
    "Bad executable (or shared library)",         // EBADEXEC
    "Bad CPU type in executable",                 // EBADARCH
    "Shared library version mismatch",            // ESHLIBVERS
    "Malformed Mach-o file",                      // EBADMACHO
    "Operation canceled",                         // ECANCELED
    "Identifier removed",                         // EIDRM
    "No message of desired type",                 // ENOMSG
    "Illegal byte sequence",                      // EILSEQ
    "Attribute not found",                        // ENOATTR
    "Bad message",                                // EBADMSG
    "EMULTIHOP (Reserved)",                       // EMULTIHOP
    "No message available on STREAM",             // ENODATA
    "ENOLINK (Reserved)",                         // ENOLINK
    "No STREAM resources",                        // ENOSR
    "Not a STREAM",                               // ENOSTR
    "Protocol error",                             // EPROTO
    "STREAM ioctl timeout",                       // ETIME
    "Operation not supported on socket",          // EOPNOTSUPP
    "Policy not found",                           // ENOPOLICY
    "State not recoverable",                      // ENOTRECOVERABLE
    "Previous owner died",                        // EOWNERDEAD
    "Interface output queue is full",             // EQFULL
};

const int m_num_errors = sizeof(mac_errlist) / sizeof(mac_errlist[0]);