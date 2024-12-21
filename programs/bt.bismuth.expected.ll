; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Box<BinaryTree> + Empty)" = type { i32, [8 x i8] }
%"programs::bt::BinaryTree" = type { i32, %"(Box<BinaryTree> + Empty)", %"(Box<BinaryTree> + Empty)" }
%"programs::bt::Empty" = type {}

@0 = private unnamed_addr constant [2 x i8] c" \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@3 = private unnamed_addr constant [10 x i8] c"\E2\94\9C\E2\94\80\E2\94\80\00", align 1
@4 = private unnamed_addr constant [10 x i8] c"\E2\94\94\E2\94\80\E2\94\80\00", align 1
@5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@6 = private unnamed_addr constant [3 x i8] c"%u\00", align 1
@7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@8 = private unnamed_addr constant [10 x i8] c"\E2\94\9C\E2\94\80\E2\94\80\00", align 1
@9 = private unnamed_addr constant [10 x i8] c"\E2\94\94\E2\94\80\E2\94\80\00", align 1

define %Unit @"programs::bt::foo"() {
entry:
  ret %Unit zeroinitializer
}

define %Unit @"programs::bt::insertBT"(ptr %0, i32 %1) {
entry:
  %n.0 = alloca ptr, align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %3 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %4 = alloca %"programs::bt::BinaryTree", align 8
  %5 = alloca %"programs::bt::Empty", align 8
  %6 = alloca %"programs::bt::Empty", align 8
  %e.0 = alloca %"programs::bt::Empty", align 8
  %7 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n = alloca ptr, align 8
  %8 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %9 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %10 = alloca %"programs::bt::BinaryTree", align 8
  %11 = alloca %"programs::bt::Empty", align 8
  %12 = alloca %"programs::bt::Empty", align 8
  %e = alloca %"programs::bt::Empty", align 8
  %13 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %bt = alloca %"programs::bt::BinaryTree", align 8
  %value = alloca i32, align 4
  %root = alloca ptr, align 8
  store ptr %0, ptr %root, align 8
  store i32 %1, ptr %value, align 4
  %root1 = load ptr, ptr %root, align 8
  %14 = load %"programs::bt::BinaryTree", ptr %root1, align 4
  store %"programs::bt::BinaryTree" %14, ptr %bt, align 4
  %15 = getelementptr %"programs::bt::BinaryTree", ptr %bt, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  %value2 = load i32, ptr %value, align 4
  %17 = icmp slt i32 %16, %value2
  br i1 %17, label %then, label %else

then:                                             ; preds = %entry
  %18 = getelementptr %"programs::bt::BinaryTree", ptr %bt, i32 0, i32 1
  %19 = load %"(Box<BinaryTree> + Empty)", ptr %18, align 4
  store %"(Box<BinaryTree> + Empty)" %19, ptr %13, align 4
  %20 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %13, i32 0, i32 0
  %21 = load %"(Box<BinaryTree> + Empty)", ptr %20, align 4
  switch %"(Box<BinaryTree> + Empty)" %21, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %then
  %22 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %13, i32 0, i32 1
  %23 = load %"programs::bt::Empty", ptr %22, align 1
  store %"programs::bt::Empty" %23, ptr %e, align 1
  %24 = getelementptr %"programs::bt::BinaryTree", ptr %bt, i32 0, i32 1
  %value3 = load i32, ptr %value, align 4
  %25 = load %"programs::bt::Empty", ptr %12, align 1
  %26 = load %"programs::bt::Empty", ptr %11, align 1
  %27 = getelementptr %"programs::bt::BinaryTree", ptr %10, i32 0, i32 0
  store i32 %value3, ptr %27, align 4
  %28 = getelementptr i32, ptr %9, i32 0, i32 0
  store i32 2, ptr %28, align 4
  %29 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %9, i32 0, i32 1
  store %"programs::bt::Empty" %25, ptr %29, align 1
  %30 = load %"(Box<BinaryTree> + Empty)", ptr %9, align 4
  %31 = getelementptr %"programs::bt::BinaryTree", ptr %10, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %30, ptr %31, align 4
  %32 = getelementptr i32, ptr %8, i32 0, i32 0
  store i32 2, ptr %32, align 4
  %33 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %8, i32 0, i32 1
  store %"programs::bt::Empty" %26, ptr %33, align 1
  %34 = load %"(Box<BinaryTree> + Empty)", ptr %8, align 4
  %35 = getelementptr %"programs::bt::BinaryTree", ptr %10, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %34, ptr %35, align 4
  %36 = load %"programs::bt::BinaryTree", ptr %10, align 4
  %37 = call ptr @GC_malloc(i64 28)
  store %"programs::bt::BinaryTree" %36, ptr %37, align 4
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
  %42 = call %Unit @"programs::bt::insertBT"(ptr %n4, i32 %value5)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %then
  br label %if-cont

else:                                             ; preds = %entry
  %43 = getelementptr %"programs::bt::BinaryTree", ptr %bt, i32 0, i32 2
  %44 = load %"(Box<BinaryTree> + Empty)", ptr %43, align 4
  store %"(Box<BinaryTree> + Empty)" %44, ptr %7, align 4
  %45 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %7, i32 0, i32 0
  %46 = load %"(Box<BinaryTree> + Empty)", ptr %45, align 4
  switch %"(Box<BinaryTree> + Empty)" %46, label %match-cont11 [
    i32 2, label %tagBranch26
    i32 1, label %tagBranch18
  ]

tagBranch26:                                      ; preds = %else
  %47 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %7, i32 0, i32 1
  %48 = load %"programs::bt::Empty", ptr %47, align 1
  store %"programs::bt::Empty" %48, ptr %e.0, align 1
  %49 = getelementptr %"programs::bt::BinaryTree", ptr %bt, i32 0, i32 2
  %value7 = load i32, ptr %value, align 4
  %50 = load %"programs::bt::Empty", ptr %6, align 1
  %51 = load %"programs::bt::Empty", ptr %5, align 1
  %52 = getelementptr %"programs::bt::BinaryTree", ptr %4, i32 0, i32 0
  store i32 %value7, ptr %52, align 4
  %53 = getelementptr i32, ptr %3, i32 0, i32 0
  store i32 2, ptr %53, align 4
  %54 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  store %"programs::bt::Empty" %50, ptr %54, align 1
  %55 = load %"(Box<BinaryTree> + Empty)", ptr %3, align 4
  %56 = getelementptr %"programs::bt::BinaryTree", ptr %4, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %55, ptr %56, align 4
  %57 = getelementptr i32, ptr %2, i32 0, i32 0
  store i32 2, ptr %57, align 4
  %58 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  store %"programs::bt::Empty" %51, ptr %58, align 1
  %59 = load %"(Box<BinaryTree> + Empty)", ptr %2, align 4
  %60 = getelementptr %"programs::bt::BinaryTree", ptr %4, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %59, ptr %60, align 4
  %61 = load %"programs::bt::BinaryTree", ptr %4, align 4
  %62 = call ptr @GC_malloc(i64 28)
  store %"programs::bt::BinaryTree" %61, ptr %62, align 4
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
  %67 = call %Unit @"programs::bt::insertBT"(ptr %n.09, i32 %value10)
  br label %match-cont11

match-cont11:                                     ; preds = %tagBranch18, %tagBranch26, %else
  br label %if-cont

if-cont:                                          ; preds = %match-cont11, %match-cont
  %root12 = load ptr, ptr %root, align 8
  %bt13 = load %"programs::bt::BinaryTree", ptr %bt, align 4
  store %"programs::bt::BinaryTree" %bt13, ptr %root12, align 4
  ret %Unit zeroinitializer
}

define %Unit @"programs::bt::printPadding"(i32 %0) {
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
  %2 = call i32 (ptr, ...) @printf(ptr @0)
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

define %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %0) {
entry:
  %n = alloca ptr, align 8
  %e.0 = alloca %"programs::bt::Empty", align 8
  %1 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n.0 = alloca ptr, align 8
  %e = alloca %"programs::bt::Empty", align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %node = alloca %"programs::bt::BinaryTree", align 8
  store %"programs::bt::BinaryTree" %0, ptr %node, align 4
  %3 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 0
  %4 = load i32, ptr %3, align 4
  %5 = call i32 (ptr, ...) @printf(ptr @1, i32 %4)
  %6 = call i32 (ptr, ...) @printf(ptr @2)
  %7 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 1
  %8 = load %"(Box<BinaryTree> + Empty)", ptr %7, align 4
  store %"(Box<BinaryTree> + Empty)" %8, ptr %2, align 4
  %9 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 0
  %10 = load %"(Box<BinaryTree> + Empty)", ptr %9, align 4
  switch %"(Box<BinaryTree> + Empty)" %10, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %11 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %12 = load %"programs::bt::Empty", ptr %11, align 1
  store %"programs::bt::Empty" %12, ptr %e, align 1
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %13 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %n.0, align 8
  %n.01 = load ptr, ptr %n.0, align 8
  %15 = load %"programs::bt::BinaryTree", ptr %n.01, align 4
  %16 = call %Unit @"programs::bt::traversePreOrder"(i32 0, ptr @3, %"programs::bt::BinaryTree" %15)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %17 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 2
  %18 = load %"(Box<BinaryTree> + Empty)", ptr %17, align 4
  store %"(Box<BinaryTree> + Empty)" %18, ptr %1, align 4
  %19 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 0
  %20 = load %"(Box<BinaryTree> + Empty)", ptr %19, align 4
  switch %"(Box<BinaryTree> + Empty)" %20, label %match-cont5 [
    i32 2, label %tagBranch22
    i32 1, label %tagBranch13
  ]

tagBranch22:                                      ; preds = %match-cont
  %21 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  %22 = load %"programs::bt::Empty", ptr %21, align 1
  store %"programs::bt::Empty" %22, ptr %e.0, align 1
  br label %match-cont5

tagBranch13:                                      ; preds = %match-cont
  %23 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  %24 = load ptr, ptr %23, align 8
  store ptr %24, ptr %n, align 8
  %n4 = load ptr, ptr %n, align 8
  %25 = load %"programs::bt::BinaryTree", ptr %n4, align 4
  %26 = call %Unit @"programs::bt::traversePreOrder"(i32 0, ptr @4, %"programs::bt::BinaryTree" %25)
  br label %match-cont5

match-cont5:                                      ; preds = %tagBranch13, %tagBranch22, %match-cont
  %27 = call i32 (ptr, ...) @printf(ptr @5)
  ret %Unit zeroinitializer
}

define %Unit @"programs::bt::traversePreOrder"(i32 %0, ptr %1, %"programs::bt::BinaryTree" %2) {
entry:
  %n = alloca ptr, align 8
  %e.0 = alloca %"programs::bt::Empty", align 8
  %3 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %n.0 = alloca ptr, align 8
  %e = alloca %"programs::bt::Empty", align 8
  %4 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %node = alloca %"programs::bt::BinaryTree", align 8
  %pointer = alloca ptr, align 8
  %padding = alloca i32, align 4
  store i32 %0, ptr %padding, align 4
  store ptr %1, ptr %pointer, align 8
  store %"programs::bt::BinaryTree" %2, ptr %node, align 4
  %padding1 = load i32, ptr %padding, align 4
  %5 = call %Unit @"programs::bt::printPadding"(i32 %padding1)
  %pointer2 = load ptr, ptr %pointer, align 8
  %6 = call i32 (ptr, ...) @printf(ptr %pointer2)
  %7 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  %9 = call i32 (ptr, ...) @printf(ptr @6, i32 %8)
  %10 = call i32 (ptr, ...) @printf(ptr @7)
  %11 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 1
  %12 = load %"(Box<BinaryTree> + Empty)", ptr %11, align 4
  store %"(Box<BinaryTree> + Empty)" %12, ptr %4, align 4
  %13 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 0
  %14 = load %"(Box<BinaryTree> + Empty)", ptr %13, align 4
  switch %"(Box<BinaryTree> + Empty)" %14, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %15 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 1
  %16 = load %"programs::bt::Empty", ptr %15, align 1
  store %"programs::bt::Empty" %16, ptr %e, align 1
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %17 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %4, i32 0, i32 1
  %18 = load ptr, ptr %17, align 8
  store ptr %18, ptr %n.0, align 8
  %padding3 = load i32, ptr %padding, align 4
  %19 = add nsw i32 %padding3, 3
  %n.04 = load ptr, ptr %n.0, align 8
  %20 = load %"programs::bt::BinaryTree", ptr %n.04, align 4
  %21 = call %Unit @"programs::bt::traversePreOrder"(i32 %19, ptr @8, %"programs::bt::BinaryTree" %20)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %22 = getelementptr %"programs::bt::BinaryTree", ptr %node, i32 0, i32 2
  %23 = load %"(Box<BinaryTree> + Empty)", ptr %22, align 4
  store %"(Box<BinaryTree> + Empty)" %23, ptr %3, align 4
  %24 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 0
  %25 = load %"(Box<BinaryTree> + Empty)", ptr %24, align 4
  switch %"(Box<BinaryTree> + Empty)" %25, label %match-cont9 [
    i32 2, label %tagBranch25
    i32 1, label %tagBranch16
  ]

tagBranch25:                                      ; preds = %match-cont
  %26 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  %27 = load %"programs::bt::Empty", ptr %26, align 1
  store %"programs::bt::Empty" %27, ptr %e.0, align 1
  br label %match-cont9

tagBranch16:                                      ; preds = %match-cont
  %28 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %3, i32 0, i32 1
  %29 = load ptr, ptr %28, align 8
  store ptr %29, ptr %n, align 8
  %padding7 = load i32, ptr %padding, align 4
  %30 = add nsw i32 %padding7, 3
  %n8 = load ptr, ptr %n, align 8
  %31 = load %"programs::bt::BinaryTree", ptr %n8, align 4
  %32 = call %Unit @"programs::bt::traversePreOrder"(i32 %30, ptr @9, %"programs::bt::BinaryTree" %31)
  br label %match-cont9

match-cont9:                                      ; preds = %tagBranch16, %tagBranch25, %match-cont
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %node = alloca ptr, align 8
  %1 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %2 = alloca %"(Box<BinaryTree> + Empty)", align 8
  %3 = alloca %"programs::bt::BinaryTree", align 8
  %4 = alloca %"programs::bt::Empty", align 8
  %5 = alloca %"programs::bt::Empty", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %6 = load %"programs::bt::Empty", ptr %5, align 1
  %7 = load %"programs::bt::Empty", ptr %4, align 1
  %8 = getelementptr %"programs::bt::BinaryTree", ptr %3, i32 0, i32 0
  store i32 5, ptr %8, align 4
  %9 = getelementptr i32, ptr %2, i32 0, i32 0
  store i32 2, ptr %9, align 4
  %10 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %2, i32 0, i32 1
  store %"programs::bt::Empty" %6, ptr %10, align 1
  %11 = load %"(Box<BinaryTree> + Empty)", ptr %2, align 4
  %12 = getelementptr %"programs::bt::BinaryTree", ptr %3, i32 0, i32 1
  store %"(Box<BinaryTree> + Empty)" %11, ptr %12, align 4
  %13 = getelementptr i32, ptr %1, i32 0, i32 0
  store i32 2, ptr %13, align 4
  %14 = getelementptr %"(Box<BinaryTree> + Empty)", ptr %1, i32 0, i32 1
  store %"programs::bt::Empty" %7, ptr %14, align 1
  %15 = load %"(Box<BinaryTree> + Empty)", ptr %1, align 4
  %16 = getelementptr %"programs::bt::BinaryTree", ptr %3, i32 0, i32 2
  store %"(Box<BinaryTree> + Empty)" %15, ptr %16, align 4
  %17 = load %"programs::bt::BinaryTree", ptr %3, align 4
  %18 = call ptr @GC_malloc(i64 28)
  store %"programs::bt::BinaryTree" %17, ptr %18, align 4
  store ptr %18, ptr %node, align 8
  %node1 = load ptr, ptr %node, align 8
  %19 = load %"programs::bt::BinaryTree", ptr %node1, align 4
  %20 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %19)
  %node2 = load ptr, ptr %node, align 8
  %21 = call %Unit @"programs::bt::insertBT"(ptr %node2, i32 6)
  %node3 = load ptr, ptr %node, align 8
  %22 = load %"programs::bt::BinaryTree", ptr %node3, align 4
  %23 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %22)
  %node4 = load ptr, ptr %node, align 8
  %24 = call %Unit @"programs::bt::insertBT"(ptr %node4, i32 2)
  %node5 = load ptr, ptr %node, align 8
  %25 = load %"programs::bt::BinaryTree", ptr %node5, align 4
  %26 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %25)
  %node6 = load ptr, ptr %node, align 8
  %27 = call %Unit @"programs::bt::insertBT"(ptr %node6, i32 3)
  %node7 = load ptr, ptr %node, align 8
  %28 = load %"programs::bt::BinaryTree", ptr %node7, align 4
  %29 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %28)
  %node8 = load ptr, ptr %node, align 8
  %30 = call %Unit @"programs::bt::insertBT"(ptr %node8, i32 4)
  %node9 = load ptr, ptr %node, align 8
  %31 = load %"programs::bt::BinaryTree", ptr %node9, align 4
  %32 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %31)
  %node10 = load ptr, ptr %node, align 8
  %33 = call %Unit @"programs::bt::insertBT"(ptr %node10, i32 7)
  %node11 = load ptr, ptr %node, align 8
  %34 = load %"programs::bt::BinaryTree", ptr %node11, align 4
  %35 = call %Unit @"programs::bt::printBT"(%"programs::bt::BinaryTree" %34)
  %36 = call ptr @malloc(i32 4)
  store i32 0, ptr %36, align 4
  %37 = load ptr, ptr %c, align 8
  %38 = call %Unit @_WriteChannel(ptr %37, ptr %36)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @GC_malloc(i64)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
