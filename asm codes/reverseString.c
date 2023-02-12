.model small
.stack 100h
.data
msg1 db 13,10, "Enter String : $"
msg2 db 13,10, "Reverse String is : $"
.code
mov ax, @data
mov ds, ax
lea dx, msg1
mov ah, 09h
int 21h
mov cx,00H
read:
mov ah, 01
int 21h
cmp al, 0dh
je ahead
push ax
inc cx
jmp read
ahead:
lea dx, msg2
mov ah,09h
int 21h
display:
mov ah,02h
pop dx
int 21h
loop display
mov ah,4ch
int 21h
end
