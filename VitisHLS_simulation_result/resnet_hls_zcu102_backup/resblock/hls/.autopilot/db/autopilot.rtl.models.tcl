set SynModuleInfo {
  {SRCNAME resblock MODELNAME resblock RTLNAME resblock IS_TOP 1
    SUBMODULES {
      {MODELNAME resblock_gmem_m_axi RTLNAME resblock_gmem_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME resblock_control_s_axi RTLNAME resblock_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME resblock_control_r_s_axi RTLNAME resblock_control_r_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME resblock_flow_control_loop_pipe RTLNAME resblock_flow_control_loop_pipe BINDTYPE interface TYPE internal_upc_flow_control INSTNAME resblock_flow_control_loop_pipe_U}
    }
  }
}
