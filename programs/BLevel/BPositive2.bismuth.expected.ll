; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %b = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 31, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %i1, 42
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  store i32 0, ptr %b, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 42, ptr %b, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %b2 = load i32, ptr %b, align 4
  %2 = call ptr @malloc(i32 4)
  store i32 %b2, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
