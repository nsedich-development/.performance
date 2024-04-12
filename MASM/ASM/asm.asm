; performance.asm - add two 32-bit integers

.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword 

.data 
sum DWORD ?
counter DWORD ?

.code
main proc
	
	mov sum, 0
	mov counter, 1

	; mov eax, 7
	; add eax, 4
	; mov sum, eax

	loop_start:
		cmp counter, 1500000000
		jg loop_end 
		; add sum, counter
		inc counter
		jmp loop_start

	loop_end:
		invoke ExitProcess, 0

main endp

end main