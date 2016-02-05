/*
 * shm_sysv.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MB 1024*1024

int main(int argc, char **argv)
{
	key_t key = ftok("/tmp/mem.temp", 1);
	if (key < 0) {
		perror("ftok");
		exit(errno);
	}
	
	int shm_id = shmget(key, 1*MB, IPC_CREAT | 0666);
	if (shm_id < 0) {
		perror("shmget");
		exit(errno);
	}
	
	void* membase = shmat(shm_id, NULL, 0);
	if (membase == (int*)-1) {
		perror("shmat");
		exit(errno);
	}
	
	*(char*)membase = 42;
	
	int ret = shmdt(membase);
	
	return 0;
}

