; ModuleID = 'WPLC.ll'
source_filename = "WPLC.ll"

@0 = private unnamed_addr constant [2 x i8] c"5\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"5\00", align 1

declare void @WriteChannel(i32, i8*)

declare i8* @ReadChannel(i32)

declare i32 @Execute(void (i32)*)

declare i8* @malloc(i32)

declare i1 @ShouldLoop(i32)

declare void @ContractChannel(i32)

declare void @WeakenChannel(i32)

define void @foo(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call i8* @ReadChannel(i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = load i32, i32* %3, align 4
  %a = alloca i32, align 4
  store i32 %4, i32* %a, align 4
  %5 = load i32, i32* %c, align 4
  %6 = call i8* @ReadChannel(i32 %5)
  %7 = bitcast i8* %6 to i32*
  %8 = load i32, i32* %7, align 4
  %b = alloca i32, align 4
  store i32 %8, i32* %b, align 4
  %9 = load i32, i32* %a, align 4
  %10 = call i32 @ReadProjection(i32 %9)
  switch i32 %10, label %matchcont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %11 = load i32, i32* %b, align 4
  call void @WriteProjection(i32 %11, i32 2)
  %12 = load i32, i32* %a, align 4
  %13 = call i8* @ReadChannel(i32 %12)
  %14 = bitcast i8* %13 to i32*
  %15 = load i32, i32* %14, align 4
  %16 = call i8* @malloc(i32 4)
  store i32 %15, i8* %16, align 4
  %17 = load i32, i32* %b, align 4
  call void @WriteChannel(i32 %17, i8* %16)
  %18 = call i8* @malloc(i32 8)
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @0, i32 0, i32 0), i8* %18, align 8
  %19 = load i32, i32* %a, align 4
  call void @WriteChannel(i32 %19, i8* %18)
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %20 = load i32, i32* %b, align 4
  call void @WriteProjection(i32 %20, i32 1)
  %21 = load i32, i32* %a, align 4
  %22 = call i8* @ReadChannel(i32 %21)
  %23 = bitcast i8* %22 to i1*
  %24 = load i1, i1* %23, align 1
  %25 = call i8* @malloc(i32 1)
  store i1 %24, i8* %25, align 1
  %26 = load i32, i32* %b, align 4
  call void @WriteChannel(i32 %26, i8* %25)
  %27 = call i8* @malloc(i32 8)
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0), i8* %27, align 8
  %28 = load i32, i32* %a, align 4
  call void @WriteChannel(i32 %28, i8* %27)
  br label %matchcont

matchcont:                                        ; preds = %tagBranch2, %tagBranch1, %entry
  ret void
}

define void @bar1(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  call void @WriteProjection(i32 %1, i32 1)
  %2 = call i8* @malloc(i32 1)
  store i1 false, i8* %2, align 1
  %3 = load i32, i32* %c, align 4
  call void @WriteChannel(i32 %3, i8* %2)
  %4 = load i32, i32* %c, align 4
  %5 = call i8* @ReadChannel(i32 %4)
  %6 = bitcast i8* %5 to i8**
  %7 = load i8*, i8** %6, align 8
  %xyz = alloca i8*, align 8
  store i8* %7, i8** %xyz, align 8
  ret void
}

define void @bar2(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call i32 @ReadProjection(i32 %1)
  switch i32 %2, label %matchcont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %3 = load i32, i32* %c, align 4
  %4 = call i8* @ReadChannel(i32 %3)
  %5 = bitcast i8* %4 to i1*
  %6 = load i1, i1* %5, align 1
  %b = alloca i1, align 1
  store i1 %6, i1* %b, align 1
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %7 = load i32, i32* %c, align 4
  %8 = call i8* @ReadChannel(i32 %7)
  %9 = bitcast i8* %8 to i32*
  %10 = load i32, i32* %9, align 4
  %i = alloca i32, align 4
  store i32 %10, i32* %i, align 4
  br label %matchcont

matchcont:                                        ; preds = %tagBranch2, %tagBranch1, %entry
  ret void
}

define void @program(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = call i32 @Execute(void (i32)* @bar1)
  %l1 = alloca i32, align 4
  store i32 %1, i32* %l1, align 4
  %2 = call i32 @Execute(void (i32)* @bar2)
  %l2 = alloca i32, align 4
  store i32 %2, i32* %l2, align 4
  %3 = call i32 @Execute(void (i32)* @foo)
  %linker = alloca i32, align 4
  store i32 %3, i32* %linker, align 4
  %l11 = load i32, i32* %l1, align 4
  %4 = call i8* @malloc(i32 4)
  store i32 %l11, i8* %4, align 4
  %5 = load i32, i32* %linker, align 4
  call void @WriteChannel(i32 %5, i8* %4)
  %l22 = load i32, i32* %l2, align 4
  %6 = call i8* @malloc(i32 4)
  store i32 %l22, i8* %6, align 4
  %7 = load i32, i32* %linker, align 4
  call void @WriteChannel(i32 %7, i8* %6)
  %8 = call i8* @malloc(i32 4)
  store i32 0, i8* %8, align 4
  %9 = load i32, i32* %c, align 4
  call void @WriteChannel(i32 %9, i8* %8)
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @ReadProjection(i32)

declare void @WriteProjection(i32, i32)
