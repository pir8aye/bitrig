# $FreeBSD$

.include <bsd.own.mk>

LIB=	llvmtransformutils

SRCDIR=	lib/Transforms/Utils
SRCS=	ASanStackFrameLayout.cpp \
	AddDiscriminators.cpp \
	BasicBlockUtils.cpp \
	BreakCriticalEdges.cpp \
	BuildLibCalls.cpp \
	BypassSlowDivision.cpp \
	CloneFunction.cpp \
	CloneModule.cpp \
	CmpInstAnalysis.cpp \
	CodeExtractor.cpp \
	CtorUtils.cpp \
	DemoteRegToStack.cpp \
	FlattenCFG.cpp \
	GlobalStatus.cpp \
	InlineFunction.cpp \
	InstructionNamer.cpp \
	IntegerDivision.cpp \
	LCSSA.cpp \
	Local.cpp \
	LoopSimplify.cpp \
	LoopUnroll.cpp \
	LoopUnrollRuntime.cpp \
	LoopUtils.cpp \
	LoopVersioning.cpp \
	LowerInvoke.cpp \
	LowerSwitch.cpp \
	Mem2Reg.cpp \
	MetaRenamer.cpp \
	ModuleUtils.cpp \
	PromoteMemoryToRegister.cpp \
	SSAUpdater.cpp \
	SimplifyCFG.cpp \
	SimplifyIndVar.cpp \
	SimplifyInstructions.cpp \
	SimplifyLibCalls.cpp \
	SplitModule.cpp \
	SymbolRewriter.cpp \
	Utils.cpp \
	UnifyFunctionExitNodes.cpp \
	ValueMapper.cpp

.if ${MK_CLANG_EXTRAS:L} != "no"
SRCS+=	Utils.cpp
.endif

TGHDRS=	Attributes \
	Intrinsics

.include "../clang.lib.mk"
