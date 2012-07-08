# $OpenBSD: LaFile.pm,v 1.7 2012/07/08 10:42:25 espie Exp $

# Copyright (c) 2007-2010 Steven Mestdagh <steven@openbsd.org>
# Copyright (c) 2012 Marc Espie <espie@openbsd.org>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

use strict;
use warnings;
use feature qw(say switch state);

package LT::LaFile;
use parent qw(LT::LaLoFile);
use File::Basename;
use LT::Archive;
use LT::Util;
use LT::Trace;

# allows special treatment for some keywords
sub set
{
	my ($self, $k, $v) = @_;

	$self->SUPER::set($k, $v);
	if ($k eq 'dependency_libs') {
		my @l = split /\s+/, $v;
		$self->{deplib_list} = \@l;
	}
}

sub deplib_list
{
	my $self = shift;
	return $self->{deplib_list}
}

# XXX not sure how much of this cruft we need
sub write
{
	my ($lainfo, $filename, $name) = @_;

	my $libname = $lainfo->stringize('libname');
	my $sharedlibname = $lainfo->stringize('dlname');
	my $staticlibname = $lainfo->stringize('old_library');
	my $librarynames = $lainfo->stringize('library_names');
	my $deplibs = $lainfo->stringize('dependency_libs');
	my $current = $lainfo->stringize('current');
	my $revision = $lainfo->stringize('revision');
	my $age = $lainfo->stringize('age');
	my $installed = $lainfo->stringize('installed');
	my $shouldnotlink = $lainfo->stringize('shouldnotlink');
	my $libdir = $lainfo->stringize('libdir');

	open(my $la, '>', $filename) or die "Cannot write $filename: $!\n";
	say "creating $filename" if $main::verbose || $main::D;
	print $la <<EOF
# $name - libtool library file
# Generated by libtool $version
#
# Please DO NOT delete this file!
# It is necessary for linking the library.

# The name that we can dlopen(3).
dlname='$sharedlibname'

# Names of this library.
library_names='$librarynames'

# The name of the static archive.
old_library='$staticlibname'

# Libraries that this one depends upon.
dependency_libs='$deplibs'

# Version information for $libname.
current=$current
age=$age
revision=$revision

# Is this an already installed library?
installed=$installed

# Should we warn about portability when linking against -modules?
shouldnotlink=$shouldnotlink

# Files to dlopen/dlpreopen
dlopen=''
dlpreopen=''

# Directory that this library needs to be installed in:
libdir='$libdir'
EOF
;
}

sub write_shared_libs_log
{
	my ($self, $origv) = @_;
	my $libname = $self->stringize('libname');
	my $v = $self->stringize('current') .'.'. $self->stringize('revision');
	if (!defined $ENV{SHARED_LIBS_LOG}) {
	       return;
	}
	my $logfile = $ENV{SHARED_LIBS_LOG};
	my $fh;
	if (! -f $logfile) {
		open ($fh, '>', $logfile);
		print $fh "# SHARED_LIBS+= <libname>      <obsd version> # <orig version>\n";
		close $fh;
	}
	open ($fh, '>>', $logfile);
	# Remove first leading 'lib', we don't want that in SHARED_LIBS_LOG.
	$libname =~ s/^lib//;
	printf $fh "SHARED_LIBS +=\t%-20s %-8s # %s\n", $libname, $v, $origv;
}

# find .la file associated with a -llib flag
# XXX pick the right one if multiple are found!
sub find
{
	my ($self, $l, $dirs) = @_;

	# sort dir search order by priority
	# XXX not fully correct yet
	my @sdirs = sort { $dirs->{$b} <=> $dirs->{$a} } keys %$dirs;
	# search in cwd as well
	unshift @sdirs, '.';
	tsay {"searching .la for $l"};
	tsay {"search path= ", join(':', @sdirs)};
	foreach my $d (@sdirs) {
		foreach my $la_candidate ("$d/lib$l.la", "$d/$l.la") {
			if (-f $la_candidate) {
				tsay {"found $la_candidate"};
				return $la_candidate;
			}
		}
	}
	tsay {".la for $l not found!"};
	return 0;
}

sub link
{
	require LT::Linker;
	return LT::Linker::LaFile->link(@_);
}

sub install
{
	my ($class, $src, $dstdir, $instprog, $instopts, $strip) = @_;

	my $srcdir = dirname($src);
	my $srcfile = basename($src);
	my $dstfile = $srcfile;

	my @opts = @$instopts;
	my @stripopts = ('--strip-debug');
	if ($$instprog[-1] =~ m/install([.-]sh)?$/) {
		push @opts, '-m', '644';
	}

	my $lainfo = $class->parse($src);
	my $sharedlib = $lainfo->{'dlname'};
	my $staticlib = $lainfo->{'old_library'};
	my $laipath = "$srcdir/$ltdir/$srcfile".'i';
	if ($staticlib) {
		# do not strip static libraries, this is done below
		my @realinstopts = @opts;
		@realinstopts = grep { $_ ne '-s' } @realinstopts;
		my $s = "$srcdir/$ltdir/$staticlib";
		my $d = "$dstdir/$staticlib";
		LT::Exec->install(@$instprog, @realinstopts, $s, $d);
		LT::Exec->install('strip', @stripopts, $d) if $strip;
	}
	if ($sharedlib) {
		my $s = "$srcdir/$ltdir/$sharedlib";
		my $d = "$dstdir/$sharedlib";
		LT::Exec->install(@$instprog, @opts, $s, $d);
	}
	if ($laipath) {
		# do not try to strip .la files
		my @realinstopts = @opts;
		@realinstopts = grep { $_ ne '-s' } @realinstopts;
		my $s = $laipath;
		my $d = "$dstdir/$dstfile";
		LT::Exec->install(@$instprog, @realinstopts, $s, $d);
	}
	# for libraries with a -release in their name
	my @libnames = split /\s+/, $lainfo->{'library_names'};
	foreach my $n (@libnames) {
		next if $n eq $sharedlib;
		unlink("$dstdir/$n");
		symlink($sharedlib, "$dstdir/$n");
	}
}


package LT::Linker::LaFile;
our @ISA = qw(LT::Linker);

use LT::Util;
use LT::Trace;
use File::Basename;

sub link
{
	my ($class, $self, $ltprog, $la, $fname, $odir, $shared, $objs, $dirs,
	    $libs, $deplibs, $libdirs, $parser, $opts) = @_;

	tsay {"creating link command for library (linked ",
		($shared) ? "dynamically" : "statically", ")"};

	my $what = ref($self);
	my @libflags;
	my @cmd;
	my $dst = ($odir eq '.') ? "$ltdir/$fname" : "$odir/$ltdir/$fname";
	if ($la =~ m/\.a$/) {
		# probably just a convenience library
		$dst = ($odir eq '.') ? "$fname" : "$odir/$fname";
	}
	my $symlinkdir = $ltdir;
	if ($odir ne '.') {
		$symlinkdir = "$odir/$ltdir";
	}
	mkdir $symlinkdir if (! -d $symlinkdir);

	tsay {"argvstring (pre resolve_la): @{$parser->{args}}"};
	my $args = $parser->resolve_la($deplibs, $libdirs);
	tsay {"argvstring (post resolve_la): @{$parser->{args}}"};
	my $orderedlibs = [];
	my $staticlibs = [];
	$parser->{args} = $args;
	$args = $parser->parse_linkargs2(\@main::Rresolved,
			\@main::libsearchdirs, $orderedlibs, $staticlibs, $dirs, $libs);
	tsay {"staticlibs = \n", join("\n", @$staticlibs)};
	tsay {"orderedlibs = @$orderedlibs"};
	my $finalorderedlibs = reverse_zap_duplicates_ref($orderedlibs);
	tsay {"final orderedlibs = @$finalorderedlibs"};

	# static linking
	if (!$shared) {
		@cmd = ('ar', 'cru', $dst);
		foreach my $a (@$staticlibs) {
			if ($a =~ m/\.a$/ && $a !~ m/_pic\.a/) {
				# extract objects from archive
				my $libfile = basename($a);
				my $xdir = "$odir/$ltdir/${la}x/$libfile";
				LT::Archive->extract($xdir, $a);
				my @kobjs = LT::Archive->get_objlist($a);
				map { $_ = "$xdir/$_"; } @kobjs;
				push @libflags, @kobjs;
			}
		}
		foreach my $k (@$finalorderedlibs) {
			my $l = $libs->{$k};
			# XXX improve test
			# this has to be done probably only with
			# convenience libraries
			next if !defined $l->{lafile};
			my $lainfo = LT::LaFile->parse($l->{lafile});
			next if ($lainfo->stringize('dlname') ne '');
			$l->find($dirs, 0, 0, $what);
			my $a = $l->{fullpath};
			if ($a =~ m/\.a$/ && $a !~ m/_pic\.a/) {
				# extract objects from archive
				my $libfile = basename $a;
				my $xdir = "$odir/$ltdir/${la}x/$libfile";
				LT::Archive->extract($xdir, $a);
				my @kobjs = LT::Archive->get_objlist($a);
				map { $_ = "$xdir/$_"; } @kobjs;
				push @libflags, @kobjs;
			}
		}
		push @cmd, @libflags if (@libflags);
		push @cmd, @$objs if (@$objs);
		LT::Exec->link(@cmd);
		LT::Exec->link('ranlib', $dst);
		return;
	}

	# dynamic linking
	my $symbolsfile;
	if ($opts->{'export-symbols'}) {
		$symbolsfile = $opts->{'export-symbols'};
	} elsif ($opts->{'export-symbols-regex'}) {
		($symbolsfile = "$odir/$ltdir/$la") =~ s/\.la$/.exp/;
		LT::Archive->get_symbollist($symbolsfile, $opts->{'export-symbols-regex'}, $objs);
	}
	my $tmp = [];
	while (my $k = shift @$finalorderedlibs) {
		my $l = $libs->{$k};
		$l->find($dirs, 1, $opts->{'static'}, $what);
		if ($l->{dropped}) {
			# remove library if dependency on it has been dropped
			delete $libs->{$k};
		} else {
			push(@$tmp, $k);
		}
	}
	$finalorderedlibs = $tmp;

	my @libobjects = values %$libs;
	tsay {"libs:\n", join("\n", (keys %$libs))};
	tsay {"libfiles:\n", 
	    join("\n", map { $_->{fullpath}//'UNDEF' } @libobjects) };

	$class->create_symlinks($symlinkdir, $libs);
	my $prev_was_archive = 0;
	my $libcounter = 0;
	foreach my $k (@$finalorderedlibs) {
		my $a = $libs->{$k}->{fullpath} || die "Link error: $k not found in \$libs\n";
		if ($a =~ m/\.a$/) {
			# don't make a -lfoo out of a static library
			push @libflags, '-Wl,-whole-archive' unless $prev_was_archive;
			push @libflags, $a;
			if ($libcounter == @$finalorderedlibs - 1) {
				push @libflags, '-Wl,-no-whole-archive';
			}
			$prev_was_archive = 1;
		} else {
			push @libflags, '-Wl,-no-whole-archive' if $prev_was_archive;
			$prev_was_archive = 0;
			my $lib = basename($a);
			if ($lib =~ m/^lib(.*)\.so(\.\d+){2}/) {
				$lib = $1;
			} else {
				say "warning: cannot derive -l flag from library filename $a, assuming hash key -l$k";
				$lib = $k;
			}
			push @libflags, "-l$lib";
		}
		$libcounter++;
	}

	@cmd = @$ltprog;
	push @cmd, $sharedflag, @picflags;
	push @cmd, '-o', $dst;
	push @cmd, @$args if $args;
	push @cmd, @$objs if @$objs;
	push @cmd, '-Wl,-whole-archive', @$staticlibs, '-Wl,-no-whole-archive'
       		if @$staticlibs;
	push @cmd, "-L$symlinkdir", @libflags if @libflags;
	push @cmd, "-Wl,-retain-symbols-file,$symbolsfile" if $symbolsfile;
	LT::Exec->link(@cmd);
}

1;
