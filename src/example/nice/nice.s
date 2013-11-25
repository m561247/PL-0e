BITS 32

EXTERN	fpc_get_output
EXTERN	fpc_write_text_sint
EXTERN	FPC_IOCHECK
EXTERN	fpc_writeln_end
EXTERN	FPC_INITIALIZEUNITS
EXTERN	FPC_DO_EXIT
EXTERN	INIT$_SYSTEM
EXTERN	THREADVARLIST_SYSTEM
EXTERN	THREADVARLIST_SI_PRC
; Begin asmlist al_begin
; End asmlist al_begin
; Begin asmlist al_stabs
; End asmlist al_stabs
; Begin asmlist al_procedures

SECTION .text
	ALIGN 16
	GLOBAL P$NICE_SWAP
P$NICE_SWAP:
..@c1:
		push	ebp
..@c3:
..@c4:
		mov	ebp,esp
..@c5:
		sub	esp,8
		mov	dword [ebp-8],ebx
		mov	ax,word [TC_P$NICE_SWAP_defaultPPt]
		mov	word [ebp-4],ax
		movsx	eax,word [ebp-4]
		inc	eax
		mov	word [ebp-4],ax
		call	NEAR fpc_get_output
		mov	ebx,eax
		movsx	ecx,word [ebp-4]
		mov	edx,ebx
		mov	eax,0
		call	NEAR fpc_write_text_sint
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		mov	ebx,dword [ebp-8]
		leave
		ret
..@c2:

SECTION .text
	ALIGN 16
	GLOBAL P$NICE_SWAP_QEE
P$NICE_SWAP_QEE:
..@c6:
		push	ebp
..@c8:
..@c9:
		mov	ebp,esp
..@c10:
		sub	esp,16
		mov	dword [ebp-16],ebx
		mov	dword [ebp-4],eax
		mov	ax,word [TC_P$NICE_SWAP_QEE_defaultUUt]
		mov	word [ebp-12],ax
		mov	ax,word [TC_P$NICE_SWAP_QEE_defaultQQv]
		mov	word [ebp-8],ax
		movsx	eax,word [ebp-8]
		inc	eax
		mov	word [ebp-8],ax
		call	NEAR fpc_get_output
		mov	ebx,eax
		movsx	ecx,word [ebp-8]
		mov	edx,ebx
		mov	eax,0
		call	NEAR fpc_write_text_sint
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		call	NEAR fpc_get_output
		mov	ebx,eax
		movsx	ecx,word [ebp-12]
		mov	edx,ebx
		mov	eax,0
		call	NEAR fpc_write_text_sint
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		mov	ebx,dword [ebp-16]
		leave
		ret
..@c7:

SECTION .text
	ALIGN 16
	GLOBAL PASCALMAIN
PASCALMAIN:
	GLOBAL main
main:
..@c11:
		push	ebp
..@c13:
..@c14:
		mov	ebp,esp
..@c15:
		call	NEAR FPC_INITIALIZEUNITS
		call	NEAR P$NICE_SWAP
		call	NEAR P$NICE_SWAP
		call	NEAR FPC_DO_EXIT
		leave
		ret
..@c12:

SECTION .text
; End asmlist al_procedures
; Begin asmlist al_globals

SECTION .data
	ALIGN 4
	GLOBAL THREADVARLIST_P$NICE
THREADVARLIST_P$NICE:
	DD	0

SECTION .data
	ALIGN 4
	GLOBAL INITFINAL
INITFINAL	DD	1,0
	DD	INIT$_SYSTEM,0

SECTION .data
	ALIGN 4
	GLOBAL FPC_THREADVARTABLES
FPC_THREADVARTABLES	DD	3
	DD	THREADVARLIST_SYSTEM,THREADVARLIST_SI_PRC,THREADVARLIST_P$NICE

SECTION .data
	ALIGN 4
	GLOBAL FPC_RESOURCESTRINGTABLES
FPC_RESOURCESTRINGTABLES	DD	0

SECTION .fpc
	ALIGN 8
		DB	"FPC 2.4.4-3.1 [2012/01/04] for i386 - Linux"

SECTION .data
	ALIGN 4
	GLOBAL __stklen
__stklen	DD	8388608

SECTION .data
	ALIGN 4
	GLOBAL __heapsize
__heapsize	DD	0

SECTION .data
	GLOBAL __fpc_valgrind
__fpc_valgrind	DB	0

SECTION .data
	ALIGN 4
	GLOBAL FPC_RESLOCATION
FPC_RESLOCATION	DD	0
; End asmlist al_globals
; Begin asmlist al_const
; End asmlist al_const
; Begin asmlist al_typedconsts

SECTION .data
	ALIGN 2
TC_P$NICE_SWAP_defaultPPt:
	DW	1

SECTION .data
	ALIGN 2
TC_P$NICE_SWAP_QEE_defaultQQv:
	DW	2

SECTION .data
	ALIGN 2
TC_P$NICE_SWAP_QEE_defaultUUt:
	DW	8
; End asmlist al_typedconsts
; Begin asmlist al_rotypedconsts
; End asmlist al_rotypedconsts
; Begin asmlist al_threadvars
; End asmlist al_threadvars
; Begin asmlist al_imports
; End asmlist al_imports
; Begin asmlist al_exports
; End asmlist al_exports
; Begin asmlist al_resources
; End asmlist al_resources
; Begin asmlist al_rtti
; End asmlist al_rtti
; Begin asmlist al_dwarf_frame

SECTION .debug_frame
..@c16:
	DD	..@c18-..@c17
..@c17:
	DD	-1
	DB	1,0
	DB	8,12
	DB	5
	ALIGN 4
..@c18:
	DD	..@c20-..@c19
..@c19:
	DD	..@c16,..@c1,..@c2-..@c1
	DB	4
	DD	..@c3-..@c1
	DB	14
	DB	4
	DD	..@c4-..@c3
	DB	5
	DB	4
	DD	..@c5-..@c4
	DB	13
	ALIGN 4
..@c20:
	DD	..@c22-..@c21
..@c21:
	DD	..@c16,..@c6,..@c7-..@c6
	DB	4
	DD	..@c8-..@c6
	DB	14
	DB	4
	DD	..@c9-..@c8
	DB	5
	DB	4
	DD	..@c10-..@c9
	DB	13
	ALIGN 4
..@c22:
	DD	..@c24-..@c23
..@c23:
	DD	..@c16,..@c11,..@c12-..@c11
	DB	4
	DD	..@c13-..@c11
	DB	14
	DB	4
	DD	..@c14-..@c13
	DB	5
	DB	4
	DD	..@c15-..@c14
	DB	13
	ALIGN 4
..@c24:
; End asmlist al_dwarf_frame
; Begin asmlist al_dwarf_info
; End asmlist al_dwarf_info
; Begin asmlist al_dwarf_abbrev
; End asmlist al_dwarf_abbrev
; Begin asmlist al_dwarf_line
; End asmlist al_dwarf_line
; Begin asmlist al_picdata
; End asmlist al_picdata
; Begin asmlist al_resourcestrings
; End asmlist al_resourcestrings
; Begin asmlist al_end
; End asmlist al_end

