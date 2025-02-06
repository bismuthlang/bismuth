; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%"(Box<BinaryTree> + Empty)" = type { i32, [8 x i8] }
%BinaryTree = type { i32, %"(Box<BinaryTree> + Empty)", %"(Box<BinaryTree> + Empty)" }
%Empty = type {}
%Unit = type {}

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [2 x i8] c" \00", align 1
@3 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@5 = private unnamed_addr constant [10 x i8] c"\E2\94\9C\E2\94\80\E2\94\80\00", align 1
@6 = private unnamed_addr constant [10 x i8] c"\E2\94\94\E2\94\80\E2\94\80\00", align 1
@7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@8 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@9 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@10 = private unnamed_addr constant [10 x i8] c"\E2\94\9C\E2\94\80\E2\94\80\00", align 1
@11 = private unnamed_addr constant [10 x i8] c"\E2\94\94\E2\94\80\E2\94\80\00", align 1

define ptr @BTWalker(%"(Box<BinaryTree> + Empty)" %0, ptr %1) {
entry:
  %a.0 = alloca ptr, align 8
  %bt = alloca %BinaryTree, align 8
  %t = alloca ptr, align 8
  %e = alloca %Empty, align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %a = alloca ptr, align 8
  %btOpt = alloca %"(Box<BinaryTree> + Empty)", align 8
  store %"(Box<BinaryTree> + Empty)" %0, ptr %btOpt, align 4
  store ptr %1, ptr %a, align 8
  %btOpt1 = load %"(Box<BinaryTree> + Empty)", ptr %btOpt, align 4
  store %"(Box<BinaryTree> + Empty)" %btOpt1, ptr %2, align 4
  %3 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 0
  %4 = load i32, ptr %3, align 4
  switch i32 %4, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %5 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %6 = load %Empty, ptr %5, align 1
  store %Empty %6, ptr %e, align 1
  %a2 = load ptr, ptr %a, align 8
  ret ptr %a2

tagBranch1:                                       ; preds = %entry
  %7 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %t, align 8
  %t3 = load ptr, ptr %t, align 8
  %9 = load %BinaryTree, ptr %t3, align 4
  store %BinaryTree %9, ptr %bt, align 4
  %10 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 1
  %11 = load %"(Box<BinaryTree> + Empty)", ptr %10, align 4
  %a4 = load ptr, ptr %a, align 8
  %12 = call ptr @BTWalker(%"(Box<BinaryTree> + Empty)" %11, ptr %a4)
  store ptr %12, ptr %a.0, align 8
  %13 = load ptr, ptr %a.0, align 8
  %14 = call %Unit @_ContractChannel(ptr %13)
  %15 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  %17 = call ptr @malloc(i32 4)
  store i32 %16, ptr %17, align 4
  %18 = load ptr, ptr %a.0, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  %20 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 2
  %21 = load %"(Box<BinaryTree> + Empty)", ptr %20, align 4
  %a.05 = load ptr, ptr %a.0, align 8
  %22 = call ptr @BTWalker(%"(Box<BinaryTree> + Empty)" %21, ptr %a.05)
  ret ptr %22

match-cont:                                       ; preds = %entry
  unreachable
}

define %Unit @BTPrinter(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call i1 @_ShouldLinearLoop(ptr %1)
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load i32, ptr %4, align 4
  %6 = call %Unit @free(ptr %4)
  %7 = call i32 (ptr, ...) @printf(ptr @0, i32 %5)
  %8 = load ptr, ptr %c, align 8
  %9 = call i1 @_ShouldLinearLoop(ptr %8)
  br i1 %9, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %10 = call i32 (ptr, ...) @printf(ptr @1)
  ret %Unit zeroinitializer
}

define %Unit @insertBT(ptr %0, i32 %1) {
entry:
  %n.0 = alloca ptr, align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %3 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %4 = alloca %BinaryTree, align 8
  %5 = alloca %Empty, align 8
  %6 = alloca %Empty, align 8
  %e.0 = alloca %Empty, align 8
  %7 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n = alloca ptr, align 8
  %8 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %9 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %10 = alloca %BinaryTree, align 8
  %11 = alloca %Empty, align 8
  %12 = alloca %Empty, align 8
  %e = alloca %Empty, align 8
  %13 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %bt = alloca %BinaryTree, align 8
  %value = alloca i32, align 4
  %root = alloca ptr, align 8
  store ptr %0, ptr %root, align 8
  store i32 %1, ptr %value, align 4
  %root1 = load ptr, ptr %root, align 8
  %14 = load %BinaryTree, ptr %root1, align 4
  store %BinaryTree %14, ptr %bt, align 4
  %15 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  %value2 = load i32, ptr %value, align 4
  %17 = icmp slt i32 %16, %value2
  br i1 %17, label %then, label %else

then:                                             ; preds = %entry
  %18 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 1
  %19 = load %"(Box<BinaryTree> + Empty)", ptr %18, align 4
  store %"(Box<BinaryTree> + Empty)" %19, ptr %13, align 4
  %20 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %13, i32 0, i32 0
  %21 = load i32, ptr %20, align 4
  switch i32 %21, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %then
  %22 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %13, i32 0, i32 1
  %23 = load %Empty, ptr %22, align 1
  store %Empty %23, ptr %e, align 1
  %24 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 1
  %value3 = load i32, ptr %value, align 4
  %25 = load %Empty, ptr %12, align 1
  %26 = load %Empty, ptr %11, align 1
  %27 = getelementptr %BinaryTree, ptr %10, i32 0, i32 0
  store i32 %value3, ptr %27, align 4
  %28 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %9, i32 0, i32 0
  store i32 2, ptr %28, align 4
  %29 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %9, i32 0, i32 1
  store %Empty %25, ptr %29, align 1
  %30 = load %"(Box<BinaryTree> + Empty)", ptr %9, align 4
  %31 = getelementptr %BinaryTree, ptr %10, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %30, ptr %31, align 4
  %32 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %8, i32 0, i32 0
  store i32 2, ptr %32, align 4
  %33 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %8, i32 0, i32 1
  store %Empty %26, ptr %33, align 1
  %34 = load %"(Box<BinaryTree> + Empty)", ptr %8, align 4
  %35 = getelementptr %BinaryTree, ptr %10, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %34, ptr %35, align 4
  %36 = load %BinaryTree, ptr %10, align 4
  %37 = call ptr @GC_malloc(i64 28)
  store %BinaryTree %36, ptr %37, align 4
  %38 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %24, i32 0, i32 0
  store i32 1, ptr %38, align 4
  %39 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %24, i32 0, i32 1
  store ptr %37, ptr %39, align 8
  br label %match-cont

tagBranch1:                                       ; preds = %then
  %40 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %13, i32 0, i32 1
  %41 = load ptr, ptr %40, align 8
  store ptr %41, ptr %n, align 8
  %n4 = load ptr, ptr %n, align 8
  %value5 = load i32, ptr %value, align 4
  %42 = call %Unit @insertBT(ptr %n4, i32 %value5)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %then
  br label %if-cont

else:                                             ; preds = %entry
  %43 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 2
  %44 = load %"(Box<BinaryTree> + Empty)", ptr %43, align 4
  store %"(Box<BinaryTree> + Empty)" %44, ptr %7, align 4
  %45 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %7, i32 0, i32 0
  %46 = load i32, ptr %45, align 4
  switch i32 %46, label %match-cont11 [
    i32 2, label %tagBranch26
    i32 1, label %tagBranch18
  ]

tagBranch26:                                      ; preds = %else
  %47 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %7, i32 0, i32 1
  %48 = load %Empty, ptr %47, align 1
  store %Empty %48, ptr %e.0, align 1
  %49 = getelementptr %BinaryTree, ptr %bt, i32 0, i32 2
  %value7 = load i32, ptr %value, align 4
  %50 = load %Empty, ptr %6, align 1
  %51 = load %Empty, ptr %5, align 1
  %52 = getelementptr %BinaryTree, ptr %4, i32 0, i32 0
  store i32 %value7, ptr %52, align 4
  %53 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 0
  store i32 2, ptr %53, align 4
  %54 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  store %Empty %50, ptr %54, align 1
  %55 = load %"(Box<BinaryTree> + Empty)", ptr %3, align 4
  %56 = getelementptr %BinaryTree, ptr %4, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %55, ptr %56, align 4
  %57 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 0
  store i32 2, ptr %57, align 4
  %58 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  store %Empty %51, ptr %58, align 1
  %59 = load %"(Box<BinaryTree> + Empty)", ptr %2, align 4
  %60 = getelementptr %BinaryTree, ptr %4, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %59, ptr %60, align 4
  %61 = load %BinaryTree, ptr %4, align 4
  %62 = call ptr @GC_malloc(i64 28)
  store %BinaryTree %61, ptr %62, align 4
  %63 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %49, i32 0, i32 0
  store i32 1, ptr %63, align 4
  %64 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %49, i32 0, i32 1
  store ptr %62, ptr %64, align 8
  br label %match-cont11

tagBranch18:                                      ; preds = %else
  %65 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %7, i32 0, i32 1
  %66 = load ptr, ptr %65, align 8
  store ptr %66, ptr %n.0, align 8
  %n.09 = load ptr, ptr %n.0, align 8
  %value10 = load i32, ptr %value, align 4
  %67 = call %Unit @insertBT(ptr %n.09, i32 %value10)
  br label %match-cont11

match-cont11:                                     ; preds = %tagBranch18, %tagBranch26, %else
  br label %if-cont

if-cont:                                          ; preds = %match-cont11, %match-cont
  %root12 = load ptr, ptr %root, align 8
  %bt13 = load %BinaryTree, ptr %bt, align 4
  store %BinaryTree %bt13, ptr %root12, align 4
  ret %Unit zeroinitializer
}

define %Unit @printSpaces(i32 %0) {
entry:
  %i = alloca i32, align 4
  %chars = alloca i32, align 4
  store i32 %0, ptr %chars, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %chars2 = load i32, ptr %chars, align 4
  %1 = icmp slt i32 %i1, %chars2
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %2 = call i32 (ptr, ...) @printf(ptr @2)
  %i3 = load i32, ptr %i, align 4
  %3 = add nsw i32 %i3, 1
  store i32 %3, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %chars5 = load i32, ptr %chars, align 4
  %4 = icmp slt i32 %i4, %chars5
  br i1 %4, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  ret %Unit zeroinitializer
}

define %Unit @printBT(%BinaryTree %0) {
entry:
  %n = alloca ptr, align 8
  %e.0 = alloca %Empty, align 8
  %1 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n.0 = alloca ptr, align 8
  %e = alloca %Empty, align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %node = alloca %BinaryTree, align 8
  store %BinaryTree %0, ptr %node, align 4
  %3 = getelementptr %BinaryTree, ptr %node, i32 0, i32 0
  %4 = load i32, ptr %3, align 4
  %5 = call i32 (ptr, ...) @printf(ptr @3, i32 %4)
  %6 = call i32 (ptr, ...) @printf(ptr @4)
  %7 = getelementptr %BinaryTree, ptr %node, i32 0, i32 1
  %8 = load %"(Box<BinaryTree> + Empty)", ptr %7, align 4
  store %"(Box<BinaryTree> + Empty)" %8, ptr %2, align 4
  %9 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 0
  %10 = load i32, ptr %9, align 4
  switch i32 %10, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %11 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %12 = load %Empty, ptr %11, align 1
  store %Empty %12, ptr %e, align 1
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %13 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %n.0, align 8
  %n.01 = load ptr, ptr %n.0, align 8
  %15 = load %BinaryTree, ptr %n.01, align 4
  %16 = call %Unit @traversePreOrder(i32 0, ptr @5, %BinaryTree %15)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %17 = getelementptr %BinaryTree, ptr %node, i32 0, i32 2
  %18 = load %"(Box<BinaryTree> + Empty)", ptr %17, align 4
  store %"(Box<BinaryTree> + Empty)" %18, ptr %1, align 4
  %19 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 0
  %20 = load i32, ptr %19, align 4
  switch i32 %20, label %match-cont5 [
    i32 2, label %tagBranch22
    i32 1, label %tagBranch13
  ]

tagBranch22:                                      ; preds = %match-cont
  %21 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  %22 = load %Empty, ptr %21, align 1
  store %Empty %22, ptr %e.0, align 1
  br label %match-cont5

tagBranch13:                                      ; preds = %match-cont
  %23 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  %24 = load ptr, ptr %23, align 8
  store ptr %24, ptr %n, align 8
  %n4 = load ptr, ptr %n, align 8
  %25 = load %BinaryTree, ptr %n4, align 4
  %26 = call %Unit @traversePreOrder(i32 0, ptr @6, %BinaryTree %25)
  br label %match-cont5

match-cont5:                                      ; preds = %tagBranch13, %tagBranch22, %match-cont
  %27 = call i32 (ptr, ...) @printf(ptr @7)
  ret %Unit zeroinitializer
}

define %Unit @traversePreOrder(i32 %0, ptr %1, %BinaryTree %2) {
entry:
  %n = alloca ptr, align 8
  %e.0 = alloca %Empty, align 8
  %3 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n.0 = alloca ptr, align 8
  %e = alloca %Empty, align 8
  %4 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %node = alloca %BinaryTree, align 8
  %prefix = alloca ptr, align 8
  %padding = alloca i32, align 4
  store i32 %0, ptr %padding, align 4
  store ptr %1, ptr %prefix, align 8
  store %BinaryTree %2, ptr %node, align 4
  %padding1 = load i32, ptr %padding, align 4
  %5 = call %Unit @printSpaces(i32 %padding1)
  %prefix2 = load ptr, ptr %prefix, align 8
  %6 = call i32 (ptr, ...) @printf(ptr %prefix2)
  %7 = getelementptr %BinaryTree, ptr %node, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  %9 = call i32 (ptr, ...) @printf(ptr @8, i32 %8)
  %10 = call i32 (ptr, ...) @printf(ptr @9)
  %11 = getelementptr %BinaryTree, ptr %node, i32 0, i32 1
  %12 = load %"(Box<BinaryTree> + Empty)", ptr %11, align 4
  store %"(Box<BinaryTree> + Empty)" %12, ptr %4, align 4
  %13 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 0
  %14 = load i32, ptr %13, align 4
  switch i32 %14, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %15 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 1
  %16 = load %Empty, ptr %15, align 1
  store %Empty %16, ptr %e, align 1
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %17 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 1
  %18 = load ptr, ptr %17, align 8
  store ptr %18, ptr %n.0, align 8
  %padding3 = load i32, ptr %padding, align 4
  %19 = add nsw i32 %padding3, 3
  %n.04 = load ptr, ptr %n.0, align 8
  %20 = load %BinaryTree, ptr %n.04, align 4
  %21 = call %Unit @traversePreOrder(i32 %19, ptr @10, %BinaryTree %20)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %22 = getelementptr %BinaryTree, ptr %node, i32 0, i32 2
  %23 = load %"(Box<BinaryTree> + Empty)", ptr %22, align 4
  store %"(Box<BinaryTree> + Empty)" %23, ptr %3, align 4
  %24 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 0
  %25 = load i32, ptr %24, align 4
  switch i32 %25, label %match-cont9 [
    i32 2, label %tagBranch25
    i32 1, label %tagBranch16
  ]

tagBranch25:                                      ; preds = %match-cont
  %26 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  %27 = load %Empty, ptr %26, align 1
  store %Empty %27, ptr %e.0, align 1
  br label %match-cont9

tagBranch16:                                      ; preds = %match-cont
  %28 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  %29 = load ptr, ptr %28, align 8
  store ptr %29, ptr %n, align 8
  %padding7 = load i32, ptr %padding, align 4
  %30 = add nsw i32 %padding7, 3
  %n8 = load ptr, ptr %n, align 8
  %31 = load %BinaryTree, ptr %n8, align 4
  %32 = call %Unit @traversePreOrder(i32 %30, ptr @11, %BinaryTree %31)
  br label %match-cont9

match-cont9:                                      ; preds = %tagBranch16, %tagBranch25, %match-cont
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %print2 = alloca ptr, align 8
  %1 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %print = alloca ptr, align 8
  %node = alloca ptr, align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %3 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %4 = alloca %BinaryTree, align 8
  %5 = alloca %Empty, align 8
  %6 = alloca %Empty, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %7 = load %Empty, ptr %6, align 1
  %8 = load %Empty, ptr %5, align 1
  %9 = getelementptr %BinaryTree, ptr %4, i32 0, i32 0
  store i32 5, ptr %9, align 4
  %10 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 0
  store i32 2, ptr %10, align 4
  %11 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  store %Empty %7, ptr %11, align 1
  %12 = load %"(Box<BinaryTree> + Empty)", ptr %3, align 4
  %13 = getelementptr %BinaryTree, ptr %4, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %12, ptr %13, align 4
  %14 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 0
  store i32 2, ptr %14, align 4
  %15 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  store %Empty %8, ptr %15, align 1
  %16 = load %"(Box<BinaryTree> + Empty)", ptr %2, align 4
  %17 = getelementptr %BinaryTree, ptr %4, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %16, ptr %17, align 4
  %18 = load %BinaryTree, ptr %4, align 4
  %19 = call ptr @GC_malloc(i64 28)
  store %BinaryTree %18, ptr %19, align 4
  store ptr %19, ptr %node, align 8
  %node1 = load ptr, ptr %node, align 8
  %20 = load %BinaryTree, ptr %node1, align 4
  %21 = call %Unit @printBT(%BinaryTree %20)
  %node2 = load ptr, ptr %node, align 8
  %22 = call %Unit @insertBT(ptr %node2, i32 6)
  %node3 = load ptr, ptr %node, align 8
  %23 = load %BinaryTree, ptr %node3, align 4
  %24 = call %Unit @printBT(%BinaryTree %23)
  %node4 = load ptr, ptr %node, align 8
  %25 = call %Unit @insertBT(ptr %node4, i32 2)
  %node5 = load ptr, ptr %node, align 8
  %26 = load %BinaryTree, ptr %node5, align 4
  %27 = call %Unit @printBT(%BinaryTree %26)
  %node6 = load ptr, ptr %node, align 8
  %28 = call %Unit @insertBT(ptr %node6, i32 3)
  %node7 = load ptr, ptr %node, align 8
  %29 = load %BinaryTree, ptr %node7, align 4
  %30 = call %Unit @printBT(%BinaryTree %29)
  %node8 = load ptr, ptr %node, align 8
  %31 = call %Unit @insertBT(ptr %node8, i32 4)
  %node9 = load ptr, ptr %node, align 8
  %32 = load %BinaryTree, ptr %node9, align 4
  %33 = call %Unit @printBT(%BinaryTree %32)
  %node10 = load ptr, ptr %node, align 8
  %34 = call %Unit @insertBT(ptr %node10, i32 7)
  %node11 = load ptr, ptr %node, align 8
  %35 = load %BinaryTree, ptr %node11, align 4
  %36 = call %Unit @printBT(%BinaryTree %35)
  %37 = call ptr @_Execute(ptr @BTPrinter)
  store ptr %37, ptr %print, align 8
  %node12 = load ptr, ptr %node, align 8
  %38 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 0
  store i32 1, ptr %38, align 4
  %39 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  store ptr %node12, ptr %39, align 8
  %40 = load %"(Box<BinaryTree> + Empty)", ptr %1, align 4
  %print13 = load ptr, ptr %print, align 8
  %41 = call ptr @BTWalker(%"(Box<BinaryTree> + Empty)" %40, ptr %print13)
  store ptr %41, ptr %print2, align 8
  %42 = load ptr, ptr %print2, align 8
  %43 = call %Unit @_WeakenChannel(ptr %42)
  %44 = call ptr @malloc(i32 4)
  store i32 0, ptr %44, align 4
  %45 = load ptr, ptr %c, align 8
  %46 = call %Unit @_WriteChannel(ptr %45, ptr %44)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare %Unit @_ContractChannel(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @GC_malloc(i64)

declare ptr @_Execute(ptr)

declare %Unit @_WeakenChannel(ptr)
