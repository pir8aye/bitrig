/*	$OpenBSD: elf.c,v 1.10 2004/10/09 20:26:57 mickey Exp $	*/

/*
 * Copyright (c) 2003 Michael Shalayeff
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR OR HIS RELATIVES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF MIND, USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/mman.h>
#include <unistd.h>
#include <a.out.h>
#include <elf_abi.h>
#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "elfuncs.h"
#include "util.h"

#if ELFSIZE == 32
#define	swap_addr	swap32
#define	swap_off	swap32
#define	swap_sword	swap32
#define	swap_word	swap32
#define	swap_sxword	swap32
#define	swap_xword	swap32
#define	swap_half	swap16
#define	swap_quarter	swap16
#define	elf_fix_header	elf32_fix_header
#define	elf_load_shdrs	elf32_load_shdrs
#define	elf_fix_shdrs	elf32_fix_shdrs
#define	elf_fix_phdrs	elf32_fix_phdrs
#define	elf_fix_sym	elf32_fix_sym
#define	elf_size	elf32_size
#define	elf_symload	elf32_symload
#define	elf2nlist	elf32_2nlist
#define	elf_shn2type	elf32_shn2type
#elif ELFSIZE == 64
#define	swap_addr	swap64
#define	swap_off	swap64
#ifdef __alpha__
#define	swap_sword	swap64
#define	swap_word	swap64
#else
#define	swap_sword	swap32
#define	swap_word	swap32
#endif
#define	swap_sxword	swap64
#define	swap_xword	swap64
#define	swap_half	swap64
#define	swap_quarter	swap16
#define	elf_fix_header	elf64_fix_header
#define	elf_load_shdrs	elf64_load_shdrs
#define	elf_fix_shdrs	elf64_fix_shdrs
#define	elf_fix_phdrs	elf64_fix_phdrs
#define	elf_fix_sym	elf64_fix_sym
#define	elf_size	elf64_size
#define	elf_symload	elf64_symload
#define	elf2nlist	elf64_2nlist
#define	elf_shn2type	elf64_shn2type
#else
#error "Unsupported ELF class"
#endif

#define	ELF_SDATA	".sdata"
#define	ELF_SBSS	".sbss"
#define	ELF_PLT		".plt"

int
elf_fix_header(Elf_Ehdr *eh)
{
	/* nothing to do */
	if (eh->e_ident[EI_DATA] == ELF_TARG_DATA)
		return (0);

	eh->e_type = swap16(eh->e_type);
	eh->e_machine = swap16(eh->e_machine);
	eh->e_version = swap32(eh->e_version);
	eh->e_entry = swap_addr(eh->e_entry);
	eh->e_phoff = swap_off(eh->e_phoff);
	eh->e_shoff = swap_off(eh->e_shoff);
	eh->e_flags = swap32(eh->e_flags);
	eh->e_ehsize = swap16(eh->e_ehsize);
	eh->e_phentsize = swap16(eh->e_phentsize);
	eh->e_phnum = swap16(eh->e_phnum);
	eh->e_shentsize = swap16(eh->e_shentsize);
	eh->e_shnum = swap16(eh->e_shnum);
	eh->e_shstrndx = swap16(eh->e_shstrndx);

	return (1);
}

Elf_Shdr *
elf_load_shdrs(const char *name, FILE *fp, off_t foff, Elf_Ehdr *head)
{
	Elf_Shdr *shdr;

	elf_fix_header(head);

	if ((shdr = malloc(head->e_shentsize * head->e_shnum)) == NULL) {
		warn("%s: malloc shdr", name);
		return (NULL);
	}

	if (fseeko(fp, foff + head->e_shoff, SEEK_SET)) {
		warn("%s: fseeko", name);
		free(shdr);
		return (NULL);
	}

	if (fread(shdr, head->e_shentsize, head->e_shnum, fp) != head->e_shnum) {
		warnx("%s: premature EOF", name);
		free(shdr);
		return (NULL);
	}

	elf_fix_shdrs(head, shdr);
	return (shdr);
}

int
elf_fix_shdrs(Elf_Ehdr *eh, Elf_Shdr *shdr)
{
	int i;

	/* nothing to do */
	if (eh->e_ident[EI_DATA] == ELF_TARG_DATA)
		return (0);

	for (i = eh->e_shnum; i--; shdr++) {
		shdr->sh_name = swap32(shdr->sh_name);
		shdr->sh_type = swap32(shdr->sh_type);
		shdr->sh_flags = swap_xword(shdr->sh_flags);
		shdr->sh_addr = swap_addr(shdr->sh_addr);
		shdr->sh_offset = swap_off(shdr->sh_offset);
		shdr->sh_size = swap_xword(shdr->sh_size);
		shdr->sh_link = swap32(shdr->sh_link);
		shdr->sh_info = swap32(shdr->sh_info);
		shdr->sh_addralign = swap_xword(shdr->sh_addralign);
		shdr->sh_entsize = swap_xword(shdr->sh_entsize);
	}

	return (1);
}

int
elf_fix_phdrs(Elf_Ehdr *eh, Elf_Phdr *phdr)
{
	int i;

	/* nothing to do */
	if (eh->e_ident[EI_DATA] == ELF_TARG_DATA)
		return (0);

	for (i = eh->e_phnum; i--; phdr++) {
		phdr->p_type = swap32(phdr->p_type);
		phdr->p_flags = swap32(phdr->p_flags);
		phdr->p_offset = swap_off(phdr->p_offset);
		phdr->p_vaddr = swap_addr(phdr->p_vaddr);
		phdr->p_paddr = swap_addr(phdr->p_paddr);
		phdr->p_filesz = swap_xword(phdr->p_filesz);
		phdr->p_memsz = swap_xword(phdr->p_memsz);
		phdr->p_align = swap_xword(phdr->p_align);
	}

	return (1);
}

int
elf_fix_sym(Elf_Ehdr *eh, Elf_Sym *sym)
{
	/* nothing to do */
	if (eh->e_ident[EI_DATA] == ELF_TARG_DATA)
		return (0);

	sym->st_name = swap32(sym->st_name);
	sym->st_shndx = swap16(sym->st_shndx);
	sym->st_value = swap_addr(sym->st_value);
	sym->st_size = swap_xword(sym->st_size);

	return (1);
}

int
elf_shn2type(u_int shn, const char *sn)
{
	switch (shn) {
#ifdef SHN_MIPS_SUNDEFINED
	case SHN_MIPS_SUNDEFINED:
#endif
	case SHN_UNDEF:
		return (N_UNDF | N_EXT);
	case SHN_ABS:
		return (N_ABS);
#ifdef SHN_MIPS_ACOMMON
	case SHN_MIPS_ACOMMON:
#endif
#ifdef SHN_MIPS_SCOMMON
	case SHN_MIPS_SCOMMON:
#endif
	case SHN_COMMON:
		return (N_COMM);
#ifdef SHN_MIPS_TEXT
	case SHN_MIPS_TEXT:
		return (N_TEXT);
#endif
#ifdef SHN_MIPS_DATA
	case SHN_MIPS_DATA:
		return (N_DATA);
#endif
	default:
		/* beyond 8 a table-driven binsearch shall be used */
		if (sn == NULL)
			return (-1);
		else if (!strcmp(sn, ELF_TEXT))
			return (N_TEXT);
		else if (!strcmp(sn, ELF_RODATA))
			return (N_SIZE);
		else if (!strcmp(sn, ELF_DATA))
			return (N_DATA);
		else if (!strcmp(sn, ELF_SDATA))
			return (N_DATA);
		else if (!strcmp(sn, ELF_BSS))
			return (N_BSS);
		else if (!strcmp(sn, ELF_SBSS))
			return (N_BSS);
		else if (!strncmp(sn, ELF_GOT, sizeof(ELF_GOT) - 1))
			return (N_DATA);
		else if (!strncmp(sn, ELF_PLT, sizeof(ELF_PLT) - 1))
			return (N_DATA);
		return (-1);
	}
}

/*
 * Devise nlist's type from Elf_Sym.
 * XXX this task is done as well in libc and kvm_mkdb.
 */
int
elf2nlist(Elf_Sym *sym, Elf_Ehdr *eh, Elf_Shdr *shdr, char *shstr, struct nlist *np)
{
	u_char stt;
	const char *sn;
	int type;

	if (sym->st_shndx < eh->e_shnum)
		sn = shstr + shdr[sym->st_shndx].sh_name;
	else
		sn = NULL;
#if 0
	{
		extern char *stab;
		printf("%d:%s %d %s\n", sym->st_shndx, sn? sn : "",
		    ELF_ST_TYPE(sym->st_info), stab + sym->st_name);
	}
#endif

	switch (stt = ELF_ST_TYPE(sym->st_info)) {
	case STT_NOTYPE:
	case STT_OBJECT:
		type = elf_shn2type(sym->st_shndx, sn);
		if (type < 0) {
			if (sn == NULL)
				np->n_other = '?';
			else
				np->n_type = stt == STT_NOTYPE? N_COMM : N_DATA;
		} else {
			/* a hack for .rodata check (; */
			if (type == N_SIZE) {
				np->n_type = N_DATA;
				np->n_other = 'r';
			} else
				np->n_type = type;
		}
		break;

	case STT_FUNC:
		type = elf_shn2type(sym->st_shndx, NULL);
		np->n_type = type < 0? N_TEXT : type;
		if (ELF_ST_BIND(sym->st_info) == STB_WEAK) {
			np->n_type = N_INDR;
			np->n_other = 'W';
		} else if (sn != NULL &&
		    strcmp(sn, ELF_INIT) &&
		    strcmp(sn, ELF_TEXT) &&
		    strcmp(sn, ELF_FINI))	/* XXX GNU compat */
			np->n_other = '?';
		break;

	case STT_SECTION:
		type = elf_shn2type(sym->st_shndx, NULL);
		if (type < 0)
			np->n_other = '?';
		else
			np->n_type = type;
		break;

	case STT_FILE:
		np->n_type = N_FN | N_EXT;
		break;

	/* XXX how about cross-nm then ? */
#ifdef STT_PARISC_MILLI
	case STT_PARISC_MILLI:
		np->n_type = N_TEXT;
		break;
#endif
	default:
		np->n_other = '?';
		break;
	}
	if (np->n_type != N_UNDF && ELF_ST_BIND(sym->st_info) != STB_LOCAL) {
		np->n_type |= N_EXT;
		if (np->n_other)
			np->n_other = toupper(np->n_other);
	}

	return (0);
}

int
elf_size(Elf_Ehdr *head, Elf_Shdr *shdr,
    u_long *ptext, u_long *pdata, u_long *pbss)
{
	int i;

	*ptext = *pdata = *pbss = 0;

	for (i = 0; i < head->e_shnum; i++) {
		if (!(shdr[i].sh_flags & SHF_ALLOC))
			;
		else if (shdr[i].sh_flags & SHF_EXECINSTR ||
		    !(shdr[i].sh_flags & SHF_WRITE))
			*ptext += shdr[i].sh_size;
		else if (shdr[i].sh_type == SHT_NOBITS)
			*pbss += shdr[i].sh_size;
		else
			*pdata += shdr[i].sh_size;
	}

	return (0);
}

int
elf_symload(const char *name, FILE *fp, off_t foff, Elf_Ehdr *eh,
    Elf_Shdr *shdr, struct nlist **pnames, struct nlist ***psnames,
    size_t *pstabsize, int *pnrawnames)
{
	long symsize, shstrsize;
	struct nlist *np;
	Elf_Sym sbuf;
	char *shstr;
	int i;

	shstrsize = shdr[eh->e_shstrndx].sh_size;
	if ((shstr = malloc(shstrsize)) == NULL) {
		warn("%s: malloc shsrt", name);
		return (1);
	}

	if (fseeko(fp, foff + shdr[eh->e_shstrndx].sh_offset, SEEK_SET)) {
		warn("%s: fseeko", name);
		free(shstr);
		return (1);
	}

	if (fread(shstr, 1, shstrsize, fp) != shstrsize) {
		warnx("%s: premature EOF", name);
		free(shstr);
		return(1);
	}

	stab = NULL;
	*pnames = NULL; *psnames = NULL;
	for (i = 0; i < eh->e_shnum; i++) {
		if (!strcmp(shstr + shdr[i].sh_name, ELF_STRTAB)) {
			*pstabsize = shdr[i].sh_size;
			if (*pstabsize > SIZE_T_MAX) {
				warnx("%s: corrupt file", name);
				free(shstr);
				return (1);
			}

			MMAP(stab, *pstabsize, PROT_READ, MAP_PRIVATE|MAP_FILE,
			    fileno(fp), foff + shdr[i].sh_offset);
			if (stab == MAP_FAILED) {
				free(shstr);
				return (1);
			}
		}
	}
	for (i = 0; i < eh->e_shnum; i++) {
		if (!strcmp(shstr + shdr[i].sh_name, ELF_SYMTAB)) {
			symsize = shdr[i].sh_size;
			if (fseeko(fp, foff + shdr[i].sh_offset, SEEK_SET)) {
				warn("%s: fseeko", name);
				if (stab)
					MUNMAP(stab, *pstabsize);
				free(shstr);
				return (1);
			}

			*pnrawnames = symsize / sizeof(sbuf);
			if ((*pnames = calloc(*pnrawnames, sizeof(*np))) == NULL) {
				warn("%s: malloc names", name);
				if (stab)
					MUNMAP(stab, *pstabsize);
				free(*pnames);
				free(shstr);
				return (1);
			}
			if ((*psnames = malloc(*pnrawnames * sizeof(np))) == NULL) {
				warn("%s: malloc snames", name);
				if (stab)
					MUNMAP(stab, *pstabsize);
				free(shstr);
				free(*pnames);
				free(*psnames);
				return (1);
			}

			for (np = *pnames; symsize > 0; symsize -= sizeof(sbuf)) {
				if (fread(&sbuf, 1, sizeof(sbuf),
				    fp) != sizeof(sbuf)) {
					warn("%s: read symbol", name);
					if (stab)
						MUNMAP(stab, *pstabsize);
					free(shstr);
					free(*pnames);
					free(*psnames);
					return (1);
				}

				elf_fix_sym(eh, &sbuf);

				if (!sbuf.st_name)
					continue;

				elf2nlist(&sbuf, eh, shdr, shstr, np);
				np->n_value = sbuf.st_value;
				np->n_un.n_strx = sbuf.st_name;
				np++;
			}
			*pnrawnames = np - *pnames;
		}
	}

	free(shstr);
	if (stab == NULL) {
		warnx("%s: no name list", name);
		if (*pnames)
			free(*pnames);
		if (*psnames)
			free(*psnames);
		return (1);
	}

	return (0);
}
