/*
 * AppArmor security module
 *
 * This file contains AppArmor file mediation function definitions.
 *
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2 of the
 * License.
 *
 *
 * This is a file of helper macros, defines for backporting newer versions
 * of apparmor to older kernels
 */
#ifndef __AA_BACKPORT_H
#define __AA_BACKPORT_H

/* 3.16 backport emulate commit 1d4457f99928a968767f6405b4a1f50845aa15fd */
#define task_no_new_privs(T) ((T)->no_new_privs)

/* 3.12 backport emulate commit b18825a7c8e37a7cf6abb97a12a6ad71af160de7 */
#define d_is_positive(D) ((D)->d_inode)

#endif /* __AA_BACKPORT_H */
