; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Box<Box<int>> + Unit)" = type { i32, [8 x i8] }

@0 = private unnamed_addr constant [12 x i8] c"%s = {b1 : \00", align 1
@1 = private unnamed_addr constant [10 x i8] c"(), b2 : \00", align 1
@2 = private unnamed_addr constant [10 x i8] c"%u, b2 : \00", align 1
@3 = private unnamed_addr constant [5 x i8] c"()}\0A\00", align 1
@4 = private unnamed_addr constant [5 x i8] c"%u}\0A\00", align 1
@5 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@6 = private unnamed_addr constant [11 x i8] c"ERROR!!!!\0A\00", align 1
@7 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@8 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@11 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@12 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@13 = private unnamed_addr constant [8 x i8] c"------\0A\00", align 1
@14 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@15 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@16 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@17 = private unnamed_addr constant [13 x i8] c"b (orig/9;9)\00", align 1

define %Unit @print(ptr %0, [2 x ptr] %1) {
entry:
  %i = alloca ptr, align 8
  %u.0 = alloca %Unit, align 8
  %2 = alloca %"(Box<Box<int>> + Unit)", align 8
  %3 = alloca %"(Box<Box<int>> + Unit)", align 8
  %4 = alloca %"(Box<Box<int>> + Unit)", align 8
  %i.0 = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %5 = alloca %"(Box<Box<int>> + Unit)", align 8
  %6 = alloca %"(Box<Box<int>> + Unit)", align 8
  %7 = alloca %"(Box<Box<int>> + Unit)", align 8
  %b = alloca [2 x ptr], align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store [2 x ptr] %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %8 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1)
  %9 = icmp slt i32 0, 2
  br i1 %9, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %10 = icmp sge i32 0, 0
  br i1 %10, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %11 = getelementptr [2 x ptr], ptr %b, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = getelementptr %"(Box<Box<int>> + Unit)", ptr %7, i32 0, i32 0
  store i32 1, ptr %13, align 4
  %14 = getelementptr %"(Box<Box<int>> + Unit)", ptr %7, i32 0, i32 1
  store ptr %12, ptr %14, align 8
  %15 = load %"(Box<Box<int>> + Unit)", ptr %7, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %16 = getelementptr %"(Box<Box<int>> + Unit)", ptr %6, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Box<Box<int>> + Unit)", ptr %6, i32 0, i32 1
  store %Unit zeroinitializer, ptr %17, align 1
  %18 = load %"(Box<Box<int>> + Unit)", ptr %6, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Box<Box<int>> + Unit)" [ %15, %accessGTZ ], [ %18, %accessBad ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess, ptr %5, align 4
  %19 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 0
  %20 = load i32, ptr %19, align 4
  switch i32 %20, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %21 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 1
  %22 = load %Unit, ptr %21, align 1
  store %Unit %22, ptr %u, align 1
  %23 = call %Unit (ptr, ...) @printf(ptr @1)
  br label %match-cont

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 1
  %25 = load ptr, ptr %24, align 8
  store ptr %25, ptr %i.0, align 8
  %i.02 = load ptr, ptr %i.0, align 8
  %26 = load ptr, ptr %i.02, align 8
  %27 = load i32, ptr %26, align 4
  %28 = call %Unit (ptr, ...) @printf(ptr @2, i32 %27)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %accessAfter
  %29 = icmp slt i32 1, 2
  br i1 %29, label %accessLTL3, label %accessBad5

accessLTL3:                                       ; preds = %match-cont
  %30 = icmp sge i32 1, 0
  br i1 %30, label %accessGTZ4, label %accessBad5

accessGTZ4:                                       ; preds = %accessLTL3
  %31 = getelementptr [2 x ptr], ptr %b, i32 0, i32 1
  %32 = load ptr, ptr %31, align 8
  %33 = getelementptr %"(Box<Box<int>> + Unit)", ptr %4, i32 0, i32 0
  store i32 1, ptr %33, align 4
  %34 = getelementptr %"(Box<Box<int>> + Unit)", ptr %4, i32 0, i32 1
  store ptr %32, ptr %34, align 8
  %35 = load %"(Box<Box<int>> + Unit)", ptr %4, align 4
  br label %accessAfter6

accessBad5:                                       ; preds = %accessLTL3, %match-cont
  %36 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 0
  store i32 2, ptr %36, align 4
  %37 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %37, align 1
  %38 = load %"(Box<Box<int>> + Unit)", ptr %3, align 4
  br label %accessAfter6

accessAfter6:                                     ; preds = %accessBad5, %accessGTZ4
  %arrayAccess7 = phi %"(Box<Box<int>> + Unit)" [ %35, %accessGTZ4 ], [ %38, %accessBad5 ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess7, ptr %2, align 4
  %39 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 0
  %40 = load i32, ptr %39, align 4
  switch i32 %40, label %match-cont11 [
    i32 2, label %tagBranch28
    i32 1, label %tagBranch19
  ]

tagBranch28:                                      ; preds = %accessAfter6
  %41 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  %42 = load %Unit, ptr %41, align 1
  store %Unit %42, ptr %u.0, align 1
  %43 = call %Unit (ptr, ...) @printf(ptr @3)
  br label %match-cont11

tagBranch19:                                      ; preds = %accessAfter6
  %44 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  %45 = load ptr, ptr %44, align 8
  store ptr %45, ptr %i, align 8
  %i10 = load ptr, ptr %i, align 8
  %46 = load ptr, ptr %i10, align 8
  %47 = load i32, ptr %46, align 4
  %48 = call %Unit (ptr, ...) @printf(ptr @4, i32 %47)
  br label %match-cont11

match-cont11:                                     ; preds = %tagBranch19, %tagBranch28, %accessAfter6
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %t = alloca i32, align 4
  %box = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Box<Box<int>> + Unit)", align 8
  %2 = alloca %"(Box<Box<int>> + Unit)", align 8
  %3 = alloca %"(Box<Box<int>> + Unit)", align 8
  %iPtr = alloca [2 x ptr], align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %4 = load ptr, ptr %c, align 8
  %5 = call ptr @_ReadLinearChannel(ptr %4)
  %6 = load [2 x ptr], ptr %5, align 8
  %7 = call %Unit @free(ptr %5)
  store [2 x ptr] %6, ptr %iPtr, align 8
  %iPtr1 = load [2 x ptr], ptr %iPtr, align 8
  %8 = call %Unit @print(ptr @5, [2 x ptr] %iPtr1)
  %9 = icmp slt i32 0, 2
  br i1 %9, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %10 = icmp sge i32 0, 0
  br i1 %10, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %11 = getelementptr [2 x ptr], ptr %iPtr, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 0
  store i32 1, ptr %13, align 4
  %14 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 1
  store ptr %12, ptr %14, align 8
  %15 = load %"(Box<Box<int>> + Unit)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %16 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %17, align 1
  %18 = load %"(Box<Box<int>> + Unit)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Box<Box<int>> + Unit)" [ %15, %accessGTZ ], [ %18, %accessBad ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess, ptr %1, align 4
  %19 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 0
  %20 = load i32, ptr %19, align 4
  switch i32 %20, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %21 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 1
  %22 = load %Unit, ptr %21, align 1
  store %Unit %22, ptr %u, align 1
  %23 = call %Unit (ptr, ...) @printf(ptr @6)
  br label %match-cont

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 1
  %25 = load ptr, ptr %24, align 8
  store ptr %25, ptr %box, align 8
  %box2 = load ptr, ptr %box, align 8
  %26 = load ptr, ptr %box2, align 8
  store i32 7, ptr %26, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %accessAfter
  %iPtr3 = load [2 x ptr], ptr %iPtr, align 8
  %27 = call %Unit @print(ptr @7, [2 x ptr] %iPtr3)
  %28 = sub nsw i32 0, 1
  %29 = call ptr @malloc(i32 4)
  store i32 %28, ptr %29, align 4
  %30 = load ptr, ptr %c, align 8
  %31 = call %Unit @_WriteChannel(ptr %30, ptr %29)
  %32 = load ptr, ptr %c, align 8
  %33 = call ptr @_ReadLinearChannel(ptr %32)
  %34 = load i32, ptr %33, align 4
  %35 = call %Unit @free(ptr %33)
  store i32 %34, ptr %t, align 4
  %iPtr4 = load [2 x ptr], ptr %iPtr, align 8
  %36 = call %Unit @print(ptr @8, [2 x ptr] %iPtr4)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u.0 = alloca i32, align 4
  %arr.0 = alloca [2 x ptr], align 8
  %shared.0 = alloca ptr, align 8
  %a.0 = alloca ptr, align 8
  %u = alloca i32, align 4
  %arr = alloca [2 x ptr], align 8
  %shared = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @foo)
  store ptr %1, ptr %a, align 8
  %2 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %2, align 4
  %3 = call ptr @GC_malloc(i64 8)
  store ptr %2, ptr %3, align 8
  store ptr %3, ptr %shared, align 8
  %4 = getelementptr [2 x ptr], ptr %arr, i32 0, i32 0
  %shared1 = load ptr, ptr %shared, align 8
  store ptr %shared1, ptr %4, align 8
  %5 = getelementptr [2 x ptr], ptr %arr, i32 0, i32 1
  %6 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %6, align 4
  %7 = call ptr @GC_malloc(i64 8)
  store ptr %6, ptr %7, align 8
  store ptr %7, ptr %5, align 8
  %8 = call %Unit (ptr, ...) @printf(ptr @9)
  %arr2 = load [2 x ptr], ptr %arr, align 8
  %9 = call %Unit @print(ptr @10, [2 x ptr] %arr2)
  %arr3 = load [2 x ptr], ptr %arr, align 8
  %10 = call ptr @_address_map_create()
  %11 = call [2 x ptr] @"_clone_Box<Box<int>>[2]"([2 x ptr] %arr3, ptr %10)
  %12 = call %Unit @_address_map_delete(ptr %10)
  %13 = call ptr @malloc(i32 16)
  store [2 x ptr] %11, ptr %13, align 8
  %14 = load ptr, ptr %a, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  %16 = load ptr, ptr %a, align 8
  %17 = call ptr @_ReadLinearChannel(ptr %16)
  %18 = load i32, ptr %17, align 4
  %19 = call %Unit @free(ptr %17)
  store i32 %18, ptr %u, align 4
  %arr4 = load [2 x ptr], ptr %arr, align 8
  %20 = call %Unit @print(ptr @11, [2 x ptr] %arr4)
  %shared5 = load ptr, ptr %shared, align 8
  %21 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %21, align 4
  store ptr %21, ptr %shared5, align 8
  %arr6 = load [2 x ptr], ptr %arr, align 8
  %22 = call %Unit @print(ptr @12, [2 x ptr] %arr6)
  %23 = sub nsw i32 0, 1
  %24 = call ptr @malloc(i32 4)
  store i32 %23, ptr %24, align 4
  %25 = load ptr, ptr %a, align 8
  %26 = call %Unit @_WriteChannel(ptr %25, ptr %24)
  %27 = call %Unit (ptr, ...) @printf(ptr @13)
  %28 = call ptr @_Execute(ptr @foo)
  store ptr %28, ptr %a.0, align 8
  %29 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %29, align 4
  %30 = call ptr @GC_malloc(i64 8)
  store ptr %29, ptr %30, align 8
  store ptr %30, ptr %shared.0, align 8
  %31 = getelementptr [2 x ptr], ptr %arr.0, i32 0, i32 0
  %shared.07 = load ptr, ptr %shared.0, align 8
  store ptr %shared.07, ptr %31, align 8
  %32 = getelementptr [2 x ptr], ptr %arr.0, i32 0, i32 1
  %shared.08 = load ptr, ptr %shared.0, align 8
  store ptr %shared.08, ptr %32, align 8
  %33 = call %Unit (ptr, ...) @printf(ptr @14)
  %arr.09 = load [2 x ptr], ptr %arr.0, align 8
  %34 = call %Unit @print(ptr @15, [2 x ptr] %arr.09)
  %arr.010 = load [2 x ptr], ptr %arr.0, align 8
  %35 = call ptr @_address_map_create()
  %36 = call [2 x ptr] @"_clone_Box<Box<int>>[2]"([2 x ptr] %arr.010, ptr %35)
  %37 = call %Unit @_address_map_delete(ptr %35)
  %38 = call ptr @malloc(i32 16)
  store [2 x ptr] %36, ptr %38, align 8
  %39 = load ptr, ptr %a.0, align 8
  %40 = call %Unit @_WriteChannel(ptr %39, ptr %38)
  %41 = load ptr, ptr %a.0, align 8
  %42 = call ptr @_ReadLinearChannel(ptr %41)
  %43 = load i32, ptr %42, align 4
  %44 = call %Unit @free(ptr %42)
  store i32 %43, ptr %u.0, align 4
  %arr.011 = load [2 x ptr], ptr %arr.0, align 8
  %45 = call %Unit @print(ptr @16, [2 x ptr] %arr.011)
  %shared.012 = load ptr, ptr %shared.0, align 8
  %46 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %46, align 4
  store ptr %46, ptr %shared.012, align 8
  %arr.013 = load [2 x ptr], ptr %arr.0, align 8
  %47 = call %Unit @print(ptr @17, [2 x ptr] %arr.013)
  %48 = sub nsw i32 0, 1
  %49 = call ptr @malloc(i32 4)
  store i32 %48, ptr %49, align 4
  %50 = load ptr, ptr %a.0, align 8
  %51 = call %Unit @_WriteChannel(ptr %50, ptr %49)
  %52 = call ptr @malloc(i32 4)
  store i32 0, ptr %52, align 4
  %53 = load ptr, ptr %c, align 8
  %54 = call %Unit @_WriteChannel(ptr %53, ptr %52)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare ptr @GC_malloc(i64)

declare ptr @_address_map_create()

define private [2 x ptr] @"_clone_Box<Box<int>>[2]"([2 x ptr] %0, ptr %1) {
entry:
  %len = alloca i32, align 4
  %idx = alloca i32, align 4
  %m = alloca ptr, align 8
  %v = alloca [2 x ptr], align 8
  store [2 x ptr] %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  store i32 0, ptr %idx, align 4
  store i32 2, ptr %len, align 4
  br label %loop-cond

loop-cond:                                        ; preds = %loop, %entry
  %2 = load i32, ptr %len, align 4
  %3 = load i32, ptr %idx, align 4
  %4 = icmp slt i32 %3, %2
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %loop-cond
  %5 = load i32, ptr %idx, align 4
  %6 = getelementptr [2 x ptr], ptr %v, i32 0, i32 %5
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @"_clone_Box<Box<int>>"(ptr %7, ptr %8)
  store ptr %9, ptr %6, align 8
  %10 = load i32, ptr %idx, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, ptr %idx, align 4
  br label %loop-cond

rest:                                             ; preds = %loop-cond
  %12 = load [2 x ptr], ptr %v, align 8
  ret [2 x ptr] %12
}

define private ptr @"_clone_Box<Box<int>>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = call ptr @"_clone_Box<int>"(ptr %8, ptr %6)
  %10 = call ptr @GC_malloc(i64 8)
  store ptr %9, ptr %10, align 8
  %11 = load ptr, ptr %m, align 8
  %12 = call %Unit @_address_map_put(ptr %11, ptr %2, ptr %10)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %10, %else ]
  ret ptr %phi
}

declare ptr @_address_map_has(ptr, ptr)

define private ptr @"_clone_Box<int>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load i32, ptr %7, align 4
  %9 = call ptr @GC_malloc(i64 8)
  store i32 %8, ptr %9, align 4
  %10 = load ptr, ptr %m, align 8
  %11 = call %Unit @_address_map_put(ptr %10, ptr %2, ptr %9)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %9, %else ]
  ret ptr %phi
}

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
