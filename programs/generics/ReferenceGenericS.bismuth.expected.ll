; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"ReferenceGenericS::Bar<boolean>" = type { i1 }
%"ReferenceGenericS::Bar<str>" = type { ptr }

define %Unit @program(ptr %0) {
entry:
  %f2 = alloca ptr, align 8
  %f1 = alloca ptr, align 8
  %b2 = alloca %"ReferenceGenericS::Bar<boolean>", align 8
  %b1 = alloca %"ReferenceGenericS::Bar<str>", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define i1 @"ReferenceGenericS::foo<boolean>"(i1 %0) {
entry:
  %k = alloca i1, align 1
  store i1 %0, ptr %k, align 1
  %k1 = load i1, ptr %k, align 1
  ret i1 %k1
}

define ptr @"ReferenceGenericS::foo<str>"(ptr %0) {
entry:
  %k = alloca ptr, align 8
  store ptr %0, ptr %k, align 8
  %k1 = load ptr, ptr %k, align 8
  ret ptr %k1
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
