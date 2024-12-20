; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %b = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define i32 @"recfunctemplate::foo<int>"(i32 %0, i32 %1) {
entry:
  %a = alloca ptr, align 8
  %i = alloca i32, align 4
  %t = alloca i32, align 4
  store i32 %0, ptr %t, align 4
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp sle i32 %i1, 0
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  %t2 = load i32, ptr %t, align 4
  ret i32 %t2

else:                                             ; preds = %entry
  %t3 = load i32, ptr %t, align 4
  ret i32 %t3
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
