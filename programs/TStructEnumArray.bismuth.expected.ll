; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%TIBB = type { [2 x ptr] }
%"(Box<Box<int>> + Unit)" = type { i32, [8 x i8] }
%ETIBBOB = type { i32, [16 x i8] }

@0 = private unnamed_addr constant [14 x i8] c"%s = {b[0] : \00", align 1
@1 = private unnamed_addr constant [12 x i8] c"(), b[1] : \00", align 1
@2 = private unnamed_addr constant [12 x i8] c"%u, b[1] : \00", align 1
@3 = private unnamed_addr constant [5 x i8] c"()}\0A\00", align 1
@4 = private unnamed_addr constant [5 x i8] c"%u}\0A\00", align 1
@5 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@6 = private unnamed_addr constant [11 x i8] c"ERROR!!!!\0A\00", align 1
@7 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@8 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@9 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@10 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@11 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@12 = private unnamed_addr constant [8 x i8] c"------\0A\00", align 1
@13 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@14 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@15 = private unnamed_addr constant [13 x i8] c"b (orig/9;9)\00", align 1

define %Unit @printTIBB(ptr %0, %TIBB %1) {
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
  %b = alloca %TIBB, align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store %TIBB %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %8 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1)
  %9 = getelementptr %TIBB, ptr %b, i32 0, i32 0
  %10 = icmp slt i32 0, 2
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %11 = icmp sge i32 0, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr [2 x ptr], ptr %9, i32 0, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr %"(Box<Box<int>> + Unit)", ptr %7, i32 0, i32 0
  store i32 1, ptr %14, align 4
  %15 = getelementptr %"(Box<Box<int>> + Unit)", ptr %7, i32 0, i32 1
  store ptr %13, ptr %15, align 8
  %16 = load %"(Box<Box<int>> + Unit)", ptr %7, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %17 = getelementptr %"(Box<Box<int>> + Unit)", ptr %6, i32 0, i32 0
  store i32 2, ptr %17, align 4
  %18 = getelementptr %"(Box<Box<int>> + Unit)", ptr %6, i32 0, i32 1
  store %Unit zeroinitializer, ptr %18, align 1
  %19 = load %"(Box<Box<int>> + Unit)", ptr %6, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Box<Box<int>> + Unit)" [ %16, %accessGTZ ], [ %19, %accessBad ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess, ptr %5, align 4
  %20 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 0
  %21 = load i32, ptr %20, align 4
  switch i32 %21, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %22 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 1
  %23 = load %Unit, ptr %22, align 1
  store %Unit %23, ptr %u, align 1
  %24 = call %Unit (ptr, ...) @printf(ptr @1)
  br label %match-cont

tagBranch1:                                       ; preds = %accessAfter
  %25 = getelementptr %"(Box<Box<int>> + Unit)", ptr %5, i32 0, i32 1
  %26 = load ptr, ptr %25, align 8
  store ptr %26, ptr %i.0, align 8
  %i.02 = load ptr, ptr %i.0, align 8
  %27 = load ptr, ptr %i.02, align 8
  %28 = load i32, ptr %27, align 4
  %29 = call %Unit (ptr, ...) @printf(ptr @2, i32 %28)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %accessAfter
  %30 = getelementptr %TIBB, ptr %b, i32 0, i32 0
  %31 = icmp slt i32 1, 2
  br i1 %31, label %accessLTL3, label %accessBad5

accessLTL3:                                       ; preds = %match-cont
  %32 = icmp sge i32 1, 0
  br i1 %32, label %accessGTZ4, label %accessBad5

accessGTZ4:                                       ; preds = %accessLTL3
  %33 = getelementptr [2 x ptr], ptr %30, i32 0, i32 1
  %34 = load ptr, ptr %33, align 8
  %35 = getelementptr %"(Box<Box<int>> + Unit)", ptr %4, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %36 = getelementptr %"(Box<Box<int>> + Unit)", ptr %4, i32 0, i32 1
  store ptr %34, ptr %36, align 8
  %37 = load %"(Box<Box<int>> + Unit)", ptr %4, align 4
  br label %accessAfter6

accessBad5:                                       ; preds = %accessLTL3, %match-cont
  %38 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 0
  store i32 2, ptr %38, align 4
  %39 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %39, align 1
  %40 = load %"(Box<Box<int>> + Unit)", ptr %3, align 4
  br label %accessAfter6

accessAfter6:                                     ; preds = %accessBad5, %accessGTZ4
  %arrayAccess7 = phi %"(Box<Box<int>> + Unit)" [ %37, %accessGTZ4 ], [ %40, %accessBad5 ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess7, ptr %2, align 4
  %41 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 0
  %42 = load i32, ptr %41, align 4
  switch i32 %42, label %match-cont11 [
    i32 2, label %tagBranch28
    i32 1, label %tagBranch19
  ]

tagBranch28:                                      ; preds = %accessAfter6
  %43 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  %44 = load %Unit, ptr %43, align 1
  store %Unit %44, ptr %u.0, align 1
  %45 = call %Unit (ptr, ...) @printf(ptr @3)
  br label %match-cont11

tagBranch19:                                      ; preds = %accessAfter6
  %46 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  %47 = load ptr, ptr %46, align 8
  store ptr %47, ptr %i, align 8
  %i10 = load ptr, ptr %i, align 8
  %48 = load ptr, ptr %i10, align 8
  %49 = load i32, ptr %48, align 4
  %50 = call %Unit (ptr, ...) @printf(ptr @4, i32 %49)
  br label %match-cont11

match-cont11:                                     ; preds = %tagBranch19, %tagBranch28, %accessAfter6
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %t.1 = alloca i32, align 4
  %i = alloca i32, align 4
  %t = alloca i32, align 4
  %box = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Box<Box<int>> + Unit)", align 8
  %2 = alloca %"(Box<Box<int>> + Unit)", align 8
  %3 = alloca %"(Box<Box<int>> + Unit)", align 8
  %iPtr = alloca %TIBB, align 8
  %4 = alloca %ETIBBOB, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load %ETIBBOB, ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  store %ETIBBOB %7, ptr %4, align 4
  %9 = getelementptr %ETIBBOB, ptr %4, i32 0, i32 0
  %10 = load i32, ptr %9, align 4
  switch i32 %10, label %match-cont7 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch26
  ]

tagBranch1:                                       ; preds = %entry
  %11 = getelementptr %ETIBBOB, ptr %4, i32 0, i32 1
  %12 = load %TIBB, ptr %11, align 8
  store %TIBB %12, ptr %iPtr, align 8
  %iPtr1 = load %TIBB, ptr %iPtr, align 8
  %13 = call %Unit @printTIBB(ptr @5, %TIBB %iPtr1)
  %14 = getelementptr %TIBB, ptr %iPtr, i32 0, i32 0
  %15 = icmp slt i32 0, 2
  br i1 %15, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %tagBranch1
  %16 = icmp sge i32 0, 0
  br i1 %16, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %17 = getelementptr [2 x ptr], ptr %14, i32 0, i32 0
  %18 = load ptr, ptr %17, align 8
  %19 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Box<Box<int>> + Unit)", ptr %3, i32 0, i32 1
  store ptr %18, ptr %20, align 8
  %21 = load %"(Box<Box<int>> + Unit)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %tagBranch1
  %22 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 0
  store i32 2, ptr %22, align 4
  %23 = getelementptr %"(Box<Box<int>> + Unit)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %23, align 1
  %24 = load %"(Box<Box<int>> + Unit)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Box<Box<int>> + Unit)" [ %21, %accessGTZ ], [ %24, %accessBad ]
  store %"(Box<Box<int>> + Unit)" %arrayAccess, ptr %1, align 4
  %25 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 0
  %26 = load i32, ptr %25, align 4
  switch i32 %26, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch12
  ]

tagBranch2:                                       ; preds = %accessAfter
  %27 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 1
  %28 = load %Unit, ptr %27, align 1
  store %Unit %28, ptr %u, align 1
  %29 = call %Unit (ptr, ...) @printf(ptr @6)
  br label %match-cont

tagBranch12:                                      ; preds = %accessAfter
  %30 = getelementptr %"(Box<Box<int>> + Unit)", ptr %1, i32 0, i32 1
  %31 = load ptr, ptr %30, align 8
  store ptr %31, ptr %box, align 8
  %box3 = load ptr, ptr %box, align 8
  %32 = load ptr, ptr %box3, align 8
  store i32 7, ptr %32, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch12, %tagBranch2, %accessAfter
  %iPtr4 = load %TIBB, ptr %iPtr, align 8
  %33 = call %Unit @printTIBB(ptr @7, %TIBB %iPtr4)
  %34 = sub nsw i32 0, 1
  %35 = call ptr @malloc(i32 4)
  store i32 %34, ptr %35, align 4
  %36 = load ptr, ptr %c, align 8
  %37 = call %Unit @_WriteChannel(ptr %36, ptr %35)
  %38 = load ptr, ptr %c, align 8
  %39 = call ptr @_ReadLinearChannel(ptr %38)
  %40 = load i32, ptr %39, align 4
  %41 = call %Unit @free(ptr %39)
  store i32 %40, ptr %t, align 4
  %iPtr5 = load %TIBB, ptr %iPtr, align 8
  %42 = call %Unit @printTIBB(ptr @8, %TIBB %iPtr5)
  br label %match-cont7

tagBranch26:                                      ; preds = %entry
  %43 = getelementptr %ETIBBOB, ptr %4, i32 0, i32 1
  %44 = load i32, ptr %43, align 4
  store i32 %44, ptr %i, align 4
  %45 = sub nsw i32 0, 1
  %46 = call ptr @malloc(i32 4)
  store i32 %45, ptr %46, align 4
  %47 = load ptr, ptr %c, align 8
  %48 = call %Unit @_WriteChannel(ptr %47, ptr %46)
  %49 = load ptr, ptr %c, align 8
  %50 = call ptr @_ReadLinearChannel(ptr %49)
  %51 = load i32, ptr %50, align 4
  %52 = call %Unit @free(ptr %50)
  store i32 %51, ptr %t.1, align 4
  br label %match-cont7

match-cont7:                                      ; preds = %tagBranch26, %match-cont, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u.0 = alloca i32, align 4
  %toSend.0 = alloca %ETIBBOB, align 8
  %tibb.0 = alloca %TIBB, align 8
  %1 = alloca %TIBB, align 8
  %array.0 = alloca [2 x ptr], align 8
  %shared.0 = alloca ptr, align 8
  %a.0 = alloca ptr, align 8
  %u = alloca i32, align 4
  %toSend = alloca %ETIBBOB, align 8
  %tibb = alloca %TIBB, align 8
  %2 = alloca %TIBB, align 8
  %array = alloca [2 x ptr], align 8
  %shared = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = call ptr @_Execute(ptr @foo)
  store ptr %3, ptr %a, align 8
  %4 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %4, align 4
  %5 = call ptr @GC_malloc(i64 8)
  store ptr %4, ptr %5, align 8
  store ptr %5, ptr %shared, align 8
  %6 = getelementptr [2 x ptr], ptr %array, i32 0, i32 0
  %shared1 = load ptr, ptr %shared, align 8
  store ptr %shared1, ptr %6, align 8
  %7 = getelementptr [2 x ptr], ptr %array, i32 0, i32 1
  %8 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %8, align 4
  %9 = call ptr @GC_malloc(i64 8)
  store ptr %8, ptr %9, align 8
  store ptr %9, ptr %7, align 8
  %array2 = load [2 x ptr], ptr %array, align 8
  %10 = getelementptr %TIBB, ptr %2, i32 0, i32 0
  store [2 x ptr] %array2, ptr %10, align 8
  %11 = load %TIBB, ptr %2, align 8
  store %TIBB %11, ptr %tibb, align 8
  %12 = getelementptr %TIBB, ptr %tibb, i32 0, i32 0
  %13 = getelementptr [2 x ptr], ptr %12, i32 0, i32 0
  %shared3 = load ptr, ptr %shared, align 8
  store ptr %shared3, ptr %13, align 8
  %tibb4 = load %TIBB, ptr %tibb, align 8
  %14 = getelementptr %ETIBBOB, ptr %toSend, i32 0, i32 0
  store i32 1, ptr %14, align 4
  %15 = getelementptr %ETIBBOB, ptr %toSend, i32 0, i32 1
  store %TIBB %tibb4, ptr %15, align 8
  %tibb5 = load %TIBB, ptr %tibb, align 8
  %16 = call %Unit @printTIBB(ptr @9, %TIBB %tibb5)
  %toSend6 = load %ETIBBOB, ptr %toSend, align 4
  %17 = call ptr @_address_map_create()
  %18 = call %ETIBBOB @_clone_ETIBBOB(%ETIBBOB %toSend6, ptr %17)
  %19 = call %Unit @_address_map_delete(ptr %17)
  %20 = call ptr @malloc(i32 20)
  store %ETIBBOB %18, ptr %20, align 4
  %21 = load ptr, ptr %a, align 8
  %22 = call %Unit @_WriteChannel(ptr %21, ptr %20)
  %23 = load ptr, ptr %a, align 8
  %24 = call ptr @_ReadLinearChannel(ptr %23)
  %25 = load i32, ptr %24, align 4
  %26 = call %Unit @free(ptr %24)
  store i32 %25, ptr %u, align 4
  %tibb7 = load %TIBB, ptr %tibb, align 8
  %27 = call %Unit @printTIBB(ptr @10, %TIBB %tibb7)
  %shared8 = load ptr, ptr %shared, align 8
  %28 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %28, align 4
  store ptr %28, ptr %shared8, align 8
  %tibb9 = load %TIBB, ptr %tibb, align 8
  %29 = call %Unit @printTIBB(ptr @11, %TIBB %tibb9)
  %30 = sub nsw i32 0, 1
  %31 = call ptr @malloc(i32 4)
  store i32 %30, ptr %31, align 4
  %32 = load ptr, ptr %a, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  %34 = call %Unit (ptr, ...) @printf(ptr @12)
  %35 = call ptr @_Execute(ptr @foo)
  store ptr %35, ptr %a.0, align 8
  %36 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %36, align 4
  %37 = call ptr @GC_malloc(i64 8)
  store ptr %36, ptr %37, align 8
  store ptr %37, ptr %shared.0, align 8
  %38 = getelementptr [2 x ptr], ptr %array.0, i32 0, i32 0
  %shared.010 = load ptr, ptr %shared.0, align 8
  store ptr %shared.010, ptr %38, align 8
  %39 = getelementptr [2 x ptr], ptr %array.0, i32 0, i32 1
  %shared.011 = load ptr, ptr %shared.0, align 8
  store ptr %shared.011, ptr %39, align 8
  %array.012 = load [2 x ptr], ptr %array.0, align 8
  %40 = getelementptr %TIBB, ptr %1, i32 0, i32 0
  store [2 x ptr] %array.012, ptr %40, align 8
  %41 = load %TIBB, ptr %1, align 8
  store %TIBB %41, ptr %tibb.0, align 8
  %42 = getelementptr %TIBB, ptr %tibb.0, i32 0, i32 0
  %43 = getelementptr [2 x ptr], ptr %42, i32 0, i32 0
  %shared.013 = load ptr, ptr %shared.0, align 8
  store ptr %shared.013, ptr %43, align 8
  %tibb.014 = load %TIBB, ptr %tibb.0, align 8
  %44 = getelementptr %ETIBBOB, ptr %toSend.0, i32 0, i32 0
  store i32 1, ptr %44, align 4
  %45 = getelementptr %ETIBBOB, ptr %toSend.0, i32 0, i32 1
  store %TIBB %tibb.014, ptr %45, align 8
  %tibb.015 = load %TIBB, ptr %tibb.0, align 8
  %46 = call %Unit @printTIBB(ptr @13, %TIBB %tibb.015)
  %toSend.016 = load %ETIBBOB, ptr %toSend.0, align 4
  %47 = call ptr @_address_map_create()
  %48 = call %ETIBBOB @_clone_ETIBBOB(%ETIBBOB %toSend.016, ptr %47)
  %49 = call %Unit @_address_map_delete(ptr %47)
  %50 = call ptr @malloc(i32 20)
  store %ETIBBOB %48, ptr %50, align 4
  %51 = load ptr, ptr %a.0, align 8
  %52 = call %Unit @_WriteChannel(ptr %51, ptr %50)
  %53 = load ptr, ptr %a.0, align 8
  %54 = call ptr @_ReadLinearChannel(ptr %53)
  %55 = load i32, ptr %54, align 4
  %56 = call %Unit @free(ptr %54)
  store i32 %55, ptr %u.0, align 4
  %tibb.017 = load %TIBB, ptr %tibb.0, align 8
  %57 = call %Unit @printTIBB(ptr @14, %TIBB %tibb.017)
  %shared.018 = load ptr, ptr %shared.0, align 8
  %58 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %58, align 4
  store ptr %58, ptr %shared.018, align 8
  %tibb.019 = load %TIBB, ptr %tibb.0, align 8
  %59 = call %Unit @printTIBB(ptr @15, %TIBB %tibb.019)
  %60 = sub nsw i32 0, 1
  %61 = call ptr @malloc(i32 4)
  store i32 %60, ptr %61, align 4
  %62 = load ptr, ptr %a.0, align 8
  %63 = call %Unit @_WriteChannel(ptr %62, ptr %61)
  %64 = call ptr @malloc(i32 4)
  store i32 0, ptr %64, align 4
  %65 = load ptr, ptr %c, align 8
  %66 = call %Unit @_WriteChannel(ptr %65, ptr %64)
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

define private %ETIBBOB @_clone_ETIBBOB(%ETIBBOB %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %ETIBBOB, align 8
  store %ETIBBOB %0, ptr %v, align 4
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %ETIBBOB, ptr %v, i32 0, i32 1
  %3 = getelementptr %ETIBBOB, ptr %v, i32 0, i32 0
  %4 = load i32, ptr %3, align 4
  switch i32 %4, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %5 = load %TIBB, ptr %2, align 8
  %6 = load ptr, ptr %m, align 8
  %7 = call %TIBB @_clone_TIBB(%TIBB %5, ptr %6)
  store %TIBB %7, ptr %2, align 8
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %8 = load i32, ptr %2, align 4
  %9 = load ptr, ptr %m, align 8
  store i32 %8, ptr %2, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %10 = load %ETIBBOB, ptr %v, align 4
  ret %ETIBBOB %10
}

define private %TIBB @_clone_TIBB(%TIBB %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %TIBB, align 8
  store %TIBB %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %TIBB, ptr %v, i32 0, i32 0
  %3 = load [2 x ptr], ptr %2, align 8
  %4 = load ptr, ptr %m, align 8
  %5 = call [2 x ptr] @"_clone_Box<Box<int>>[2]"([2 x ptr] %3, ptr %4)
  store [2 x ptr] %5, ptr %2, align 8
  %6 = load %TIBB, ptr %v, align 8
  ret %TIBB %6
}

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
  %2 = load i32, ptr %idx, align 4
  %3 = load i32, ptr %len, align 4
  %4 = icmp slt i32 %2, %3
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
  %6 = load ptr, ptr %v, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @"_clone_Box<int>"(ptr %7, ptr %8)
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
  %6 = load ptr, ptr %v, align 8
  %7 = load i32, ptr %6, align 4
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @GC_malloc(i64 8)
  store i32 %7, ptr %9, align 4
  %10 = load ptr, ptr %m, align 8
  %11 = call %Unit @_address_map_put(ptr %10, ptr %2, ptr %9)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %9, %else ]
  ret ptr %phi
}

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
