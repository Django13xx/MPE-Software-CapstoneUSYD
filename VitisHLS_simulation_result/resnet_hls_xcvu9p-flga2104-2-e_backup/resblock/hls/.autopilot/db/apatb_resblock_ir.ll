; ModuleID = 'X:/Xilinx/unified_workspace/resnet_hls/resblock/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_resblock_ir([56 x [56 x float]]* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="64" "maxi" %input, [56 x [56 x float]]* noalias nocapture nonnull "fpga.decayed.dim.hint"="64" "maxi" %output) local_unnamed_addr #0 {
entry:
  %0 = bitcast [56 x [56 x float]]* %input to [64 x [56 x [56 x float]]]*
  %1 = call i8* @malloc(i64 802816)
  %input_copy = bitcast i8* %1 to [64 x [56 x [56 x float]]]*
  %2 = bitcast [56 x [56 x float]]* %output to [64 x [56 x [56 x float]]]*
  %3 = call i8* @malloc(i64 802816)
  %output_copy = bitcast i8* %3 to [64 x [56 x [56 x float]]]*
  call fastcc void @copy_in([64 x [56 x [56 x float]]]* nonnull %0, [64 x [56 x [56 x float]]]* %input_copy, [64 x [56 x [56 x float]]]* nonnull %2, [64 x [56 x [56 x float]]]* %output_copy)
  call void @apatb_resblock_hw([64 x [56 x [56 x float]]]* %input_copy, [64 x [56 x [56 x float]]]* %output_copy)
  call void @copy_back([64 x [56 x [56 x float]]]* %0, [64 x [56 x [56 x float]]]* %input_copy, [64 x [56 x [56 x float]]]* %2, [64 x [56 x [56 x float]]]* %output_copy)
  tail call void @free(i8* %1)
  tail call void @free(i8* %3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in([64 x [56 x [56 x float]]]* readonly, [64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]* readonly, [64 x [56 x [56 x float]]]*) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %1, [64 x [56 x [56 x float]]]* %0)
  call fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %3, [64 x [56 x [56 x float]]]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %dst, [64 x [56 x [56 x float]]]* readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq [64 x [56 x [56 x float]]]* %dst, null
  %1 = icmp eq [64 x [56 x [56 x float]]]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* nonnull %dst, [64 x [56 x [56 x float]]]* nonnull %src, i64 64)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %dst, [64 x [56 x [56 x float]]]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [64 x [56 x [56 x float]]]* %src, null
  %1 = icmp eq [64 x [56 x [56 x float]]]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [64 x [56 x [56 x float]]], [64 x [56 x [56 x float]]]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [64 x [56 x [56 x float]]], [64 x [56 x [56 x float]]]* %src, i64 0, i64 %for.loop.idx2
  call void @arraycpy_hls.p0a56a56f32([56 x [56 x float]]* %dst.addr, [56 x [56 x float]]* %src.addr, i64 56)
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a56a56f32([56 x [56 x float]]* %dst, [56 x [56 x float]]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [56 x [56 x float]]* %src, null
  %1 = icmp eq [56 x [56 x float]]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [56 x [56 x float]], [56 x [56 x float]]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [56 x [56 x float]], [56 x [56 x float]]* %src, i64 0, i64 %for.loop.idx2
  call void @arraycpy_hls.p0a56f32([56 x float]* %dst.addr, [56 x float]* %src.addr, i64 56)
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define void @arraycpy_hls.p0a56f32([56 x float]* %dst, [56 x float]* readonly %src, i64 %num) local_unnamed_addr #3 {
entry:
  %0 = icmp eq [56 x float]* %src, null
  %1 = icmp eq [56 x float]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [56 x float], [56 x float]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [56 x float], [56 x float]* %src, i64 0, i64 %for.loop.idx2
  %3 = load float, float* %src.addr, align 4
  store float %3, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out([64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]* readonly, [64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]* readonly) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %0, [64 x [56 x [56 x float]]]* %1)
  call fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %2, [64 x [56 x [56 x float]]]* %3)
  ret void
}

declare i8* @malloc(i64) local_unnamed_addr

declare void @free(i8*) local_unnamed_addr

declare void @apatb_resblock_hw([64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]*)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back([64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]* readonly, [64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]* readonly) unnamed_addr #4 {
entry:
  call fastcc void @onebyonecpy_hls.p0a64a56a56f32([64 x [56 x [56 x float]]]* %2, [64 x [56 x [56 x float]]]* %3)
  ret void
}

declare void @resblock_hw_stub([56 x [56 x float]]* noalias nocapture nonnull readonly, [56 x [56 x float]]* noalias nocapture nonnull)

define void @resblock_hw_stub_wrapper([64 x [56 x [56 x float]]]*, [64 x [56 x [56 x float]]]*) #5 {
entry:
  call void @copy_out([64 x [56 x [56 x float]]]* null, [64 x [56 x [56 x float]]]* %0, [64 x [56 x [56 x float]]]* null, [64 x [56 x [56 x float]]]* %1)
  %2 = bitcast [64 x [56 x [56 x float]]]* %0 to [56 x [56 x float]]*
  %3 = bitcast [64 x [56 x [56 x float]]]* %1 to [56 x [56 x float]]*
  call void @resblock_hw_stub([56 x [56 x float]]* %2, [56 x [56 x float]]* %3)
  call void @copy_in([64 x [56 x [56 x float]]]* null, [64 x [56 x [56 x float]]]* %0, [64 x [56 x [56 x float]]]* null, [64 x [56 x [56 x float]]]* %1)
  ret void
}

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="arraycpy_hls" }
attributes #4 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
