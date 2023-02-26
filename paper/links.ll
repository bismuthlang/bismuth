; ModuleID = 'WPLC.ll'
source_filename = "WPLC.ll"

@0 = private unnamed_addr constant [4 x i8] c"54\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"57\0A\00", align 1

define void @linkRecvInt(i32 %0, i32 %1) {
entry:
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  %b = alloca i32, align 4
  store i32 %1, i32* %b, align 4
  %2 = load i32, i32* %a, align 4
  %3 = call i8* @ReadChannel(i32 %2)
  %4 = bitcast i8* %3 to i32*
  %5 = load i32, i32* %4, align 4
  call void @free(i8* %3)
  %6 = call i8* @malloc(i32 4)
  %7 = bitcast i8* %6 to i32*
  store i32 %5, i32* %7, align 4
  %8 = load i32, i32* %b, align 4
  call void @WriteChannel(i32 %8, i8* %6)
  ret void
}

define void @linkRecvBool(i32 %0, i32 %1) {
entry:
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  %b = alloca i32, align 4
  store i32 %1, i32* %b, align 4
  %2 = load i32, i32* %a, align 4
  %3 = call i8* @ReadChannel(i32 %2)
  %4 = bitcast i8* %3 to i1*
  %5 = load i1, i1* %4, align 1
  call void @free(i8* %3)
  %6 = call i8* @malloc(i32 1)
  %7 = bitcast i8* %6 to i1*
  store i1 %5, i1* %7, align 1
  %8 = load i32, i32* %b, align 4
  call void @WriteChannel(i32 %8, i8* %6)
  ret void
}

define void @foo(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call i8* @ReadChannel(i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = load i32, i32* %3, align 4
  call void @free(i8* %2)
  %a = alloca i32, align 4
  store i32 %4, i32* %a, align 4
  %5 = load i32, i32* %c, align 4
  %6 = call i8* @ReadChannel(i32 %5)
  %7 = bitcast i8* %6 to i32*
  %8 = load i32, i32* %7, align 4
  call void @free(i8* %6)
  %b = alloca i32, align 4
  store i32 %8, i32* %b, align 4
  %9 = load i32, i32* %a, align 4
  %10 = call i32 @ReadProjection(i32 %9)
  switch i32 %10, label %matchcont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %11 = load i32, i32* %a, align 4
  %12 = call i8* @ReadChannel(i32 %11)
  %13 = bitcast i8* %12 to i32*
  %14 = load i32, i32* %13, align 4
  call void @free(i8* %12)
  %i = alloca i32, align 4
  store i32 %14, i32* %i, align 4
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0))
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %16 = load i32, i32* %a, align 4
  %17 = call i8* @ReadChannel(i32 %16)
  %18 = bitcast i8* %17 to i1*
  %19 = load i1, i1* %18, align 1
  call void @free(i8* %17)
  %b1 = alloca i1, align 1
  store i1 %19, i1* %b1, align 1
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0))
  br label %matchcont

matchcont:                                        ; preds = %tagBranch2, %tagBranch1, %entry
  %21 = load i32, i32* %b, align 4
  call void @WriteProjection(i32 %21, i32 2)
  %22 = call i8* @malloc(i32 4)
  %23 = bitcast i8* %22 to i32*
  store i32 0, i32* %23, align 4
  %24 = load i32, i32* %b, align 4
  call void @WriteChannel(i32 %24, i8* %22)
  ret void
}

define void @bar1(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  call void @WriteProjection(i32 %1, i32 1)
  %2 = call i8* @malloc(i32 1)
  %3 = bitcast i8* %2 to i1*
  store i1 false, i1* %3, align 1
  %4 = load i32, i32* %c, align 4
  call void @WriteChannel(i32 %4, i8* %2)
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
  call void @free(i8* %4)
  %b = alloca i1, align 1
  store i1 %6, i1* %b, align 1
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %7 = load i32, i32* %c, align 4
  %8 = call i8* @ReadChannel(i32 %7)
  %9 = bitcast i8* %8 to i32*
  %10 = load i32, i32* %9, align 4
  call void @free(i8* %8)
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
  %5 = bitcast i8* %4 to i32*
  store i32 %l11, i32* %5, align 4
  %6 = load i32, i32* %linker, align 4
  call void @WriteChannel(i32 %6, i8* %4)
  %l22 = load i32, i32* %l2, align 4
  %7 = call i8* @malloc(i32 4)
  %8 = bitcast i8* %7 to i32*
  store i32 %l22, i32* %8, align 4
  %9 = load i32, i32* %linker, align 4
  call void @WriteChannel(i32 %9, i8* %7)
  %10 = call i8* @malloc(i32 4)
  %11 = bitcast i8* %10 to i32*
  store i32 0, i32* %11, align 4
  %12 = load i32, i32* %c, align 4
  call void @WriteChannel(i32 %12, i8* %10)
  ret void
}

declare i32 @printf(i8*, ...)

declare i8* @ReadChannel(i32)

declare void @free(i8*)

declare i8* @malloc(i32)

declare void @WriteChannel(i32, i8*)

declare i32 @ReadProjection(i32)

declare void @WriteProjection(i32, i32)

declare i32 @Execute(void (i32)*)
