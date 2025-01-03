; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + u32)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [12 x i8] c"%s[%d] = %d\00", align 1
@1 = private unnamed_addr constant [3 x i8] c", \00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@3 = private unnamed_addr constant [11 x i8] c"In AddOne\0A\00", align 1
@4 = private unnamed_addr constant [18 x i8] c"Exiting add one!\0A\00", align 1
@5 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@6 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@7 = private unnamed_addr constant [32 x i8] c"------------------------------\0A\00", align 1
@8 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@9 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@10 = private unnamed_addr constant [32 x i8] c"------------------------------\0A\00", align 1
@11 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@12 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@13 = private unnamed_addr constant [32 x i8] c"------------------------------\0A\00", align 1
@14 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@15 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@16 = private unnamed_addr constant [32 x i8] c"------------------------------\0A\00", align 1
@17 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@18 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@19 = private unnamed_addr constant [32 x i8] c"------------------------------\0A\00", align 1

define %Unit @printInt5Array(ptr %0) {
entry:
  %1 = alloca %"(Unit + u32)", align 8
  %2 = alloca %"(Unit + u32)", align 8
  %i = alloca i32, align 4
  %array = alloca [5 x i32], align 4
  %name = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load ptr, ptr %4, align 8
  %6 = call %Unit @free(ptr %4)
  store ptr %5, ptr %name, align 8
  %7 = load ptr, ptr %c, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load [5 x i32], ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store [5 x i32] %9, ptr %array, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %11 = icmp slt i32 %i1, 5
  br i1 %11, label %loop, label %rest

loop:                                             ; preds = %else, %entry
  %name2 = load ptr, ptr %name, align 8
  %i3 = load i32, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %12 = icmp slt i32 %i4, 5
  br i1 %12, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %13 = icmp sge i32 %i4, 0
  br i1 %13, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %14 = getelementptr [5 x i32], ptr %array, i32 0, i32 %i4
  %15 = load i32, ptr %14, align 4
  %16 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  store i32 %15, ptr %17, align 4
  %18 = load %"(Unit + u32)", ptr %2, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %19 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + u32)", ptr %1, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  %22 = call i32 @"printInt5Array::#lambda"(%"(Unit + u32)" %arrayAccess)
  %23 = call i32 (...) @printf(ptr @0, ptr %name2, i32 %i3, i32 %22)
  %i5 = load i32, ptr %i, align 4
  %24 = add nsw i32 %i5, 1
  %25 = icmp slt i32 %24, 5
  br i1 %25, label %then, label %else

then:                                             ; preds = %accessAfter
  %26 = call i32 (...) @printf(ptr @1)
  br label %else

else:                                             ; preds = %then, %accessAfter
  %i6 = load i32, ptr %i, align 4
  %27 = add nsw i32 %i6, 1
  store i32 %27, ptr %i, align 4
  %i7 = load i32, ptr %i, align 4
  %28 = icmp slt i32 %i7, 5
  br i1 %28, label %loop, label %rest

rest:                                             ; preds = %else, %entry
  %29 = call i32 (...) @printf(ptr @2)
  ret %Unit zeroinitializer
}

define %Unit @addOneToInt5(ptr %0) {
entry:
  %i = alloca i32, align 4
  %array = alloca [5 x i32], align 4
  %name = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %name, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load [5 x i32], ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  store [5 x i32] %7, ptr %array, align 4
  %9 = call i32 (...) @printf(ptr @3)
  %name1 = load ptr, ptr %name, align 8
  %array2 = load [5 x i32], ptr %array, align 4
  %10 = call i32 @syncExec(ptr @printInt5Array, ptr %name1, [5 x i32] %array2)
  store i32 0, ptr %i, align 4
  %i3 = load i32, ptr %i, align 4
  %11 = icmp slt i32 %i3, 5
  br i1 %11, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %i4 = load i32, ptr %i, align 4
  %12 = getelementptr [5 x i32], ptr %array, i32 0, i32 %i4
  %array5 = load [5 x i32], ptr %array, align 4
  %i6 = load i32, ptr %i, align 4
  %13 = call i32 @"addOneToInt5::#lambda"([5 x i32] %array5, i32 %i6)
  store i32 %13, ptr %12, align 4
  %i7 = load i32, ptr %i, align 4
  %14 = add nsw i32 %i7, 1
  store i32 %14, ptr %i, align 4
  %i8 = load i32, ptr %i, align 4
  %15 = icmp slt i32 %i8, 5
  br i1 %15, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %name9 = load ptr, ptr %name, align 8
  %array10 = load [5 x i32], ptr %array, align 4
  %16 = call i32 @syncExec(ptr @printInt5Array, ptr %name9, [5 x i32] %array10)
  %17 = call i32 (...) @printf(ptr @4)
  ret %Unit zeroinitializer
}

define i32 @syncExec(ptr %0, ptr %1, [5 x i32] %2) {
entry:
  %chan = alloca ptr, align 8
  %a = alloca [5 x i32], align 4
  %s = alloca ptr, align 8
  %prog = alloca ptr, align 8
  store ptr %0, ptr %prog, align 8
  store ptr %1, ptr %s, align 8
  store [5 x i32] %2, ptr %a, align 4
  %prog1 = load ptr, ptr %prog, align 8
  %3 = call ptr @_Execute(ptr %prog1)
  store ptr %3, ptr %chan, align 8
  %s2 = load ptr, ptr %s, align 8
  %4 = call ptr @malloc(i32 8)
  store ptr %s2, ptr %4, align 8
  %5 = load ptr, ptr %chan, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %a3 = load [5 x i32], ptr %a, align 4
  %7 = call ptr @malloc(i32 20)
  store [5 x i32] %a3, ptr %7, align 4
  %8 = load ptr, ptr %chan, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = sub nsw i32 0, 1
  ret i32 %10
}

define %Unit @program(ptr %0) {
entry:
  %i.0 = alloca i32, align 4
  %b = alloca [5 x i32], align 4
  %i = alloca i32, align 4
  %a = alloca [5 x i32], align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %i1, 5
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %i2 = load i32, ptr %i, align 4
  %2 = getelementptr [5 x i32], ptr %a, i32 0, i32 %i2
  %i3 = load i32, ptr %i, align 4
  store i32 %i3, ptr %2, align 4
  %i4 = load i32, ptr %i, align 4
  %3 = add nsw i32 %i4, 1
  store i32 %3, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %4 = icmp slt i32 %i5, 5
  br i1 %4, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %a6 = load [5 x i32], ptr %a, align 4
  %5 = call i32 @syncExec(ptr @printInt5Array, ptr @5, [5 x i32] %a6)
  store i32 0, ptr %i.0, align 4
  %i.07 = load i32, ptr %i.0, align 4
  %6 = icmp slt i32 %i.07, 5
  br i1 %6, label %loop8, label %rest12

loop8:                                            ; preds = %loop8, %rest
  %i.09 = load i32, ptr %i.0, align 4
  %7 = getelementptr [5 x i32], ptr %b, i32 0, i32 %i.09
  store i32 0, ptr %7, align 4
  %i.010 = load i32, ptr %i.0, align 4
  %8 = add nsw i32 %i.010, 1
  store i32 %8, ptr %i.0, align 4
  %i.011 = load i32, ptr %i.0, align 4
  %9 = icmp slt i32 %i.011, 5
  br i1 %9, label %loop8, label %rest12

rest12:                                           ; preds = %loop8, %rest
  %b13 = load [5 x i32], ptr %b, align 4
  %10 = call i32 @syncExec(ptr @printInt5Array, ptr @6, [5 x i32] %b13)
  %11 = call i32 (...) @printf(ptr @7)
  %a14 = load [5 x i32], ptr %a, align 4
  %12 = call i32 @syncExec(ptr @printInt5Array, ptr @8, [5 x i32] %a14)
  %b15 = load [5 x i32], ptr %b, align 4
  %13 = call i32 @syncExec(ptr @printInt5Array, ptr @9, [5 x i32] %b15)
  %14 = call i32 (...) @printf(ptr @10)
  %a16 = load [5 x i32], ptr %a, align 4
  store [5 x i32] %a16, ptr %b, align 4
  %a17 = load [5 x i32], ptr %a, align 4
  %15 = call i32 @syncExec(ptr @printInt5Array, ptr @11, [5 x i32] %a17)
  %b18 = load [5 x i32], ptr %b, align 4
  %16 = call i32 @syncExec(ptr @printInt5Array, ptr @12, [5 x i32] %b18)
  %17 = call i32 (...) @printf(ptr @13)
  %18 = getelementptr [5 x i32], ptr %a, i32 0, i32 3
  store i32 1000, ptr %18, align 4
  %19 = getelementptr [5 x i32], ptr %b, i32 0, i32 0
  store i32 9999, ptr %19, align 4
  %a19 = load [5 x i32], ptr %a, align 4
  %20 = call i32 @syncExec(ptr @printInt5Array, ptr @14, [5 x i32] %a19)
  %b20 = load [5 x i32], ptr %b, align 4
  %21 = call i32 @syncExec(ptr @printInt5Array, ptr @15, [5 x i32] %b20)
  %22 = call i32 (...) @printf(ptr @16)
  %a21 = load [5 x i32], ptr %a, align 4
  %23 = call i32 @syncExec(ptr @addOneToInt5, ptr @17, [5 x i32] %a21)
  %a22 = load [5 x i32], ptr %a, align 4
  %24 = call i32 @syncExec(ptr @printInt5Array, ptr @18, [5 x i32] %a22)
  %25 = call i32 (...) @printf(ptr @19)
  %26 = call ptr @malloc(i32 4)
  store i32 0, ptr %26, align 4
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private i32 @"printInt5Array::#lambda"(%"(Unit + u32)" %0) {
entry:
  %u = alloca %Unit, align 8
  %i = alloca i32, align 4
  %1 = alloca %"(Unit + u32)", align 8
  %a = alloca %"(Unit + u32)", align 8
  store %"(Unit + u32)" %0, ptr %a, align 4
  %a1 = load %"(Unit + u32)", ptr %a, align 4
  store %"(Unit + u32)" %a1, ptr %1, align 4
  %2 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 0
  %3 = load i32, ptr %2, align 4
  switch i32 %3, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %4 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  ret i32 %i2

tagBranch1:                                       ; preds = %entry
  %6 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 1
  %7 = load %Unit, ptr %6, align 1
  store %Unit %7, ptr %u, align 1
  %8 = sub nsw i32 0, 1
  ret i32 %8

match-cont:                                       ; preds = %entry
  unreachable
}

define private i32 @"addOneToInt5::#lambda"([5 x i32] %0, i32 %1) {
entry:
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + u32)", align 8
  %3 = alloca %"(Unit + u32)", align 8
  %4 = alloca %"(Unit + u32)", align 8
  %idx = alloca i32, align 4
  %a = alloca [5 x i32], align 4
  store [5 x i32] %0, ptr %a, align 4
  store i32 %1, ptr %idx, align 4
  %idx1 = load i32, ptr %idx, align 4
  %5 = icmp slt i32 %idx1, 5
  br i1 %5, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %6 = icmp sge i32 %idx1, 0
  br i1 %6, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %7 = getelementptr [5 x i32], ptr %a, i32 0, i32 %idx1
  %8 = load i32, ptr %7, align 4
  %9 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 0
  store i32 2, ptr %9, align 4
  %10 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 1
  store i32 %8, ptr %10, align 4
  %11 = load %"(Unit + u32)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %12 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 0
  store i32 1, ptr %12, align 4
  %13 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %13, align 1
  %14 = load %"(Unit + u32)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32)" [ %11, %accessGTZ ], [ %14, %accessBad ]
  store %"(Unit + u32)" %arrayAccess, ptr %2, align 4
  %15 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  switch i32 %16, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %17 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  %18 = load %Unit, ptr %17, align 1
  store %Unit %18, ptr %u, align 1
  %19 = sub nsw i32 0, 1
  ret i32 %19

tagBranch2:                                       ; preds = %accessAfter
  %20 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  %21 = load i32, ptr %20, align 4
  store i32 %21, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %22 = add nsw i32 %i2, 1
  ret i32 %22

match-cont:                                       ; preds = %accessAfter
  unreachable
}

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
