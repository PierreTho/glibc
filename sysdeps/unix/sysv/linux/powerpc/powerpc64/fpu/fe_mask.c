/* Procedure definition for FE_MASK_ENV for Linux/ppc64.
   Copyright (C) 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv.h>
#include <errno.h>
#include <sysdep.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <kernel-features.h>

const fenv_t *
__fe_mask_env (void)
{
#if defined PR_SET_FPEXC && defined PR_FP_EXC_DISABLED
  int result;
  INTERNAL_SYSCALL_DECL (err);
  result = INTERNAL_SYSCALL (prctl, err, 2, PR_SET_FPEXC, PR_FP_EXC_DISABLED);
# ifndef __ASSUME_NEW_PRCTL_SYSCALL
  if (INTERNAL_SYSCALL_ERROR_P (result, err)
      && INTERNAL_SYSCALL_ERRNO (result, err) == EINVAL)
    __set_errno (ENOSYS);
# endif
#else
  __set_errno (ENOSYS);
#endif
  return FE_DFL_ENV;
}
