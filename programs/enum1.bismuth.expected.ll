; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%a = type { i32, [8 x i8] }
%b = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [13 x i8] c"hello there!\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"Integer\0A\00", align 1
@2 = private unnamed_addr constant [10 x i8] c"Boolean!\0A\00", align 1
@3 = private unnamed_addr constant [9 x i8] c"Integer\0A\00", align 1
@4 = private unnamed_addr constant [10 x i8] c"Boolean!\0A\00", align 1
@5 = private unnamed_addr constant [6 x i8] c"%s!!\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %b = alloca i1, align 1
  %a.0 = alloca i32, align 4
  %1 = alloca %a, align 8
  %b.0 = alloca i1, align 1
  %a = alloca i32, align 4
  %2 = alloca %b, align 8
  %oth1 = alloca %b, align 8
  %idkStr = alloca %a, align 8
  %idk2 = alloca %a, align 8
  %idk1 = alloca %a, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = getelementptr %a, ptr %idk1, i32 0, i32 0
  store i32 2, ptr %3, align 4
  %4 = getelementptr %a, ptr %idk1, i32 0, i32 1
  store i32 1, ptr %4, align 4
  %5 = getelementptr %a, ptr %idk2, i32 0, i32 0
  store i32 1, ptr %5, align 4
  %6 = getelementptr %a, ptr %idk2, i32 0, i32 1
  store i1 false, ptr %6, align 1
  %7 = getelementptr %a, ptr %idkStr, i32 0, i32 0
  store i32 3, ptr %7, align 4
  %8 = getelementptr %a, ptr %idkStr, i32 0, i32 1
  store ptr @0, ptr %8, align 8
  %9 = icmp eq i32 1, 4
  %10 = getelementptr %b, ptr %oth1, i32 0, i32 0
  store i32 1, ptr %10, align 4
  %11 = getelementptr %b, ptr %oth1, i32 0, i32 1
  store i1 %9, ptr %11, align 1
  %oth11 = load %b, ptr %oth1, align 4
  store %b %oth11, ptr %2, align 4
  %12 = getelementptr %b, ptr %2, i32 0, i32 0
  %13 = load i32, ptr %12, align 4
  switch i32 %13, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %14 = getelementptr %b, ptr %2, i32 0, i32 1
  %15 = load i32, ptr %14, align 4
  store i32 %15, ptr %a, align 4
  %16 = call i32 (ptr, ...) @printf(ptr @1)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %17 = getelementptr %b, ptr %2, i32 0, i32 1
  %18 = load i1, ptr %17, align 1
  store i1 %18, ptr %b.0, align 1
  %19 = call i32 (ptr, ...) @printf(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %idkStr2 = load %a, ptr %idkStr, align 4
  store %a %idkStr2, ptr %1, align 4
  %20 = getelementptr %a, ptr %1, i32 0, i32 0
  %21 = load i32, ptr %20, align 4
  switch i32 %21, label %match-cont6 [
    i32 2, label %tagBranch23
    i32 1, label %tagBranch14
    i32 3, label %tagBranch3
  ]

tagBranch23:                                      ; preds = %match-cont
  %22 = getelementptr %a, ptr %1, i32 0, i32 1
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %a.0, align 4
  %24 = call i32 (ptr, ...) @printf(ptr @3)
  br label %match-cont6

tagBranch14:                                      ; preds = %match-cont
  %25 = getelementptr %a, ptr %1, i32 0, i32 1
  %26 = load i1, ptr %25, align 1
  store i1 %26, ptr %b, align 1
  %27 = call i32 (ptr, ...) @printf(ptr @4)
  br label %match-cont6

tagBranch3:                                       ; preds = %match-cont
  %28 = getelementptr %a, ptr %1, i32 0, i32 1
  %29 = load ptr, ptr %28, align 8
  store ptr %29, ptr %s, align 8
  %s5 = load ptr, ptr %s, align 8
  %30 = call i32 (ptr, ...) @printf(ptr @5, ptr %s5)
  br label %match-cont6

match-cont6:                                      ; preds = %tagBranch3, %tagBranch14, %tagBranch23, %match-cont
  %31 = call ptr @malloc(i32 4)
  store i32 0, ptr %31, align 4
  %32 = load ptr, ptr %c, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
