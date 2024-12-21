; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [13 x i8] c"a[%i] := %i\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"TRUE\0A\00", align 1
@2 = private unnamed_addr constant [7 x i8] c"FALSE\0A\00", align 1
@3 = private unnamed_addr constant [17 x i8] c"Why hello there!\00", align 1
@4 = private unnamed_addr constant [34 x i8] c"Well, we fell into the first case\00", align 1
@5 = private unnamed_addr constant [35 x i8] c"ERROR: THIS CODE SHOULDN'T BE RUN\0A\00", align 1
@6 = private unnamed_addr constant [23 x i8] c"Second case this time!\00", align 1
@7 = private unnamed_addr constant [17 x i8] c"Why hello there!\00", align 1
@8 = private unnamed_addr constant [33 x i8] c"Well, we fel into the first case\00", align 1
@9 = private unnamed_addr constant [23 x i8] c"Second case this time!\00", align 1
@10 = private unnamed_addr constant [35 x i8] c"ERROR: THIS CODE SHOULDN'T BE RUN\0A\00", align 1
@11 = private unnamed_addr constant [14 x i8] c"Hello World!\0A\00", align 1
@12 = private unnamed_addr constant [10 x i8] c"C is: %i\0A\00", align 1
@13 = private unnamed_addr constant [15 x i8] c"C is %i; a = [\00", align 1
@14 = private unnamed_addr constant [8 x i8] c"ERROR, \00", align 1
@15 = private unnamed_addr constant [5 x i8] c"%i, \00", align 1
@16 = private unnamed_addr constant [3 x i8] c"]\0A\00", align 1
@17 = private unnamed_addr constant [20 x i8] c"From test, got: %i\0A\00", align 1
@18 = private unnamed_addr constant [20 x i8] c"Other test, got %i\0A\00", align 1
@19 = private unnamed_addr constant [22 x i8] c"Other other test, %s\0A\00", align 1
@20 = private unnamed_addr constant [28 x i8] c"Other other other test, %s\0A\00", align 1

define %Unit @"programs::test1::chayos"(ptr %0) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 1, ptr %a, align 4
  store i32 1, ptr %b, align 4
  %b1 = load i32, ptr %b, align 4
  store i32 %b1, ptr %a, align 4
  %1 = sub nsw i32 0, 1
  %2 = call ptr @malloc(i32 4)
  store i32 %1, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

define %Unit @"programs::test1::idk"(ptr %0) {
entry:
  %x = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = icmp slt i32 1, 2
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  store i32 3, ptr %x, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 2, ptr %x, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %x1 = load i32, ptr %x, align 4
  %2 = call ptr @malloc(i32 4)
  store i32 %x1, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

define %Unit @"programs::test1::branchtest"(ptr %0) {
entry:
  %count = alloca i32, align 4
  %a = alloca [5 x i32], align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %count, align 4
  %count1 = load i32, ptr %count, align 4
  %1 = icmp slt i32 %count1, 5
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %count2 = load i32, ptr %count, align 4
  %2 = getelementptr [5 x i32], ptr %a, i32 0, i32 %count2
  %count3 = load i32, ptr %count, align 4
  store i32 %count3, ptr %2, align 4
  %count4 = load i32, ptr %count, align 4
  %count5 = load i32, ptr %count, align 4
  %3 = call i32 (...) @printf(ptr @0, i32 %count4, i32 %count5)
  %count6 = load i32, ptr %count, align 4
  %4 = add nsw i32 %count6, 1
  store i32 %4, ptr %count, align 4
  %count7 = load i32, ptr %count, align 4
  %5 = icmp slt i32 %count7, 5
  br i1 %5, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  br i1 true, label %then, label %else

then:                                             ; preds = %rest
  %6 = call i32 (...) @printf(ptr @1)
  %7 = sub nsw i32 0, 1
  %8 = call ptr @malloc(i32 4)
  store i32 %7, ptr %8, align 4
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  br label %if-cont

else:                                             ; preds = %rest
  %11 = call i32 (...) @printf(ptr @2)
  %12 = sub nsw i32 0, 22
  %13 = call ptr @malloc(i32 4)
  store i32 %12, ptr %13, align 4
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  ret %Unit zeroinitializer
}

define %Unit @"programs::test1::otherbranch"(ptr %0) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %a, align 4
  store i32 1, ptr %b, align 4
  %a1 = load i32, ptr %a, align 4
  %1 = icmp slt i32 %a1, 5
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  store i32 3, ptr %b, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 5, ptr %b, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %b2 = load i32, ptr %b, align 4
  %2 = call ptr @malloc(i32 4)
  store i32 %b2, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

define %Unit @"programs::test1::otherbranchtwo"(ptr %0) {
entry:
  %b = alloca ptr, align 8
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %a, align 4
  store ptr @3, ptr %b, align 8
  %a1 = load i32, ptr %a, align 4
  %1 = icmp slt i32 %a1, 5
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  store ptr @4, ptr %b, align 8
  br label %if-cont

else:                                             ; preds = %entry
  %2 = call i32 (...) @printf(ptr @5)
  store ptr @6, ptr %b, align 8
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %b2 = load ptr, ptr %b, align 8
  %3 = call ptr @malloc(i32 8)
  store ptr %b2, ptr %3, align 8
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  ret %Unit zeroinitializer
}

define %Unit @"programs::test1::otherbranchthree"(ptr %0) {
entry:
  %cb = alloca ptr, align 8
  %ca = alloca ptr, align 8
  %b = alloca ptr, align 8
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %a, align 4
  store ptr @7, ptr %b, align 8
  store ptr @8, ptr %ca, align 8
  store ptr @9, ptr %cb, align 8
  %a1 = load i32, ptr %a, align 4
  %1 = icmp slt i32 %a1, 5
  %2 = xor i1 %1, true
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  %3 = call i32 (...) @printf(ptr @10)
  %ca2 = load ptr, ptr %ca, align 8
  store ptr %ca2, ptr %b, align 8
  br label %if-cont

else:                                             ; preds = %entry
  %cb3 = load ptr, ptr %cb, align 8
  store ptr %cb3, ptr %b, align 8
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %b4 = load ptr, ptr %b, align 8
  %4 = call ptr @malloc(i32 8)
  store ptr %b4, ptr %4, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %t4a = alloca ptr, align 8
  %t3a = alloca ptr, align 8
  %t2a = alloca i32, align 4
  %t1a = alloca i32, align 4
  %t4 = alloca ptr, align 8
  %t3 = alloca ptr, align 8
  %t2 = alloca ptr, align 8
  %t1 = alloca ptr, align 8
  %v = alloca i32, align 4
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %c = alloca i32, align 4
  %a = alloca [50 x i32], align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %4 = call i32 (...) @printf(ptr @11)
  store i32 2, ptr %c, align 4
  %c1 = load i32, ptr %c, align 4
  %5 = call i32 (...) @printf(ptr @12, i32 %c1)
  %6 = getelementptr [50 x i32], ptr %a, i32 0, i32 0
  store i32 1, ptr %6, align 4
  %7 = getelementptr [50 x i32], ptr %a, i32 0, i32 1
  store i32 2, ptr %7, align 4
  %8 = getelementptr [50 x i32], ptr %a, i32 0, i32 2
  store i32 3, ptr %8, align 4
  %9 = getelementptr [50 x i32], ptr %a, i32 0, i32 3
  store i32 4, ptr %9, align 4
  %10 = getelementptr [50 x i32], ptr %a, i32 0, i32 4
  store i32 5, ptr %10, align 4
  %c2 = load i32, ptr %c, align 4
  %11 = call i32 (...) @printf(ptr @13, i32 %c2)
  store i32 0, ptr %i, align 4
  %i3 = load i32, ptr %i, align 4
  %12 = icmp slt i32 %i3, 5
  br i1 %12, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i4 = load i32, ptr %i, align 4
  %13 = icmp slt i32 %i4, 50
  br i1 %13, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %14 = icmp sge i32 %i4, 0
  br i1 %14, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %15 = getelementptr [50 x i32], ptr %a, i32 0, i32 %i4
  %16 = load i32, ptr %15, align 4
  %17 = getelementptr i32, ptr %3, i32 0, i32 0
  store i32 2, ptr %17, align 4
  %18 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store i32 %16, ptr %18, align 4
  %19 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %20 = getelementptr i32, ptr %2, i32 0, i32 0
  store i32 1, ptr %20, align 4
  %21 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %21, align 1
  %22 = load %"(Unit + int)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %19, %accessGTZ ], [ %22, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %1, align 4
  %23 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %24 = load i32, ptr %23, align 4
  switch i32 %24, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %25 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %26 = load %Unit, ptr %25, align 1
  store %Unit %26, ptr %u, align 1
  %27 = call i32 (...) @printf(ptr @14)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %28 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %29 = load i32, ptr %28, align 4
  store i32 %29, ptr %v, align 4
  %v5 = load i32, ptr %v, align 4
  %30 = call i32 (...) @printf(ptr @15, i32 %v5)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i6 = load i32, ptr %i, align 4
  %31 = add nsw i32 %i6, 1
  store i32 %31, ptr %i, align 4
  %i7 = load i32, ptr %i, align 4
  %32 = icmp slt i32 %i7, 5
  br i1 %32, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  %33 = call i32 (...) @printf(ptr @16)
  %34 = call ptr @_Execute(ptr @"programs::test1::branchtest")
  store ptr %34, ptr %t1, align 8
  %35 = call ptr @_Execute(ptr @"programs::test1::otherbranch")
  store ptr %35, ptr %t2, align 8
  %36 = call ptr @_Execute(ptr @"programs::test1::otherbranchtwo")
  store ptr %36, ptr %t3, align 8
  %37 = call ptr @_Execute(ptr @"programs::test1::otherbranchthree")
  store ptr %37, ptr %t4, align 8
  %38 = load ptr, ptr %t1, align 8
  %39 = call ptr @_ReadLinearChannel(ptr %38)
  %40 = load i32, ptr %39, align 4
  %41 = call %Unit @free(ptr %39)
  store i32 %40, ptr %t1a, align 4
  %42 = load ptr, ptr %t2, align 8
  %43 = call ptr @_ReadLinearChannel(ptr %42)
  %44 = load i32, ptr %43, align 4
  %45 = call %Unit @free(ptr %43)
  store i32 %44, ptr %t2a, align 4
  %46 = load ptr, ptr %t3, align 8
  %47 = call ptr @_ReadLinearChannel(ptr %46)
  %48 = load ptr, ptr %47, align 8
  %49 = call %Unit @free(ptr %47)
  store ptr %48, ptr %t3a, align 8
  %50 = load ptr, ptr %t4, align 8
  %51 = call ptr @_ReadLinearChannel(ptr %50)
  %52 = load ptr, ptr %51, align 8
  %53 = call %Unit @free(ptr %51)
  store ptr %52, ptr %t4a, align 8
  %t1a8 = load i32, ptr %t1a, align 4
  %54 = call i32 (...) @printf(ptr @17, i32 %t1a8)
  %t2a9 = load i32, ptr %t2a, align 4
  %55 = call i32 (...) @printf(ptr @18, i32 %t2a9)
  %t3a10 = load ptr, ptr %t3a, align 8
  %56 = call i32 (...) @printf(ptr @19, ptr %t3a10)
  %t4a11 = load ptr, ptr %t4a, align 8
  %57 = call i32 (...) @printf(ptr @20, ptr %t4a11)
  %58 = sub nsw i32 0, 1
  %59 = call ptr @malloc(i32 4)
  store i32 %58, ptr %59, align 4
  %60 = load ptr, ptr %io, align 8
  %61 = call %Unit @_WriteChannel(ptr %60, ptr %59)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
