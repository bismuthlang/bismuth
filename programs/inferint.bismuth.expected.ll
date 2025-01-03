; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 4)
  store i32 0, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  store i32 10, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %4 = icmp slt i32 %a1, 30
  br i1 %4, label %then, label %else

then:                                             ; preds = %entry
  br label %else

else:                                             ; preds = %then, %entry
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
