#ifndef CIS_ADMISSION_SYSCALL_DATA_H
#define CIS_ADMISSION_SYSCALL_DATA_H


struct SyscallData {    // for i368 max arg number is 6
    int64_t syscall_number;
    int64_t arg_num;
    int64_t arg1;
    int64_t arg2;
    int64_t arg3;
    int64_t arg4;
    int64_t arg5;
    int64_t arg6;
};

#endif //CIS_ADMISSION_SYSCALL_DATA_H
