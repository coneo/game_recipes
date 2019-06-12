#define FSM_TRANSITION_DEF
    FSM_TRANSITION_DEF(t_be_hit, tBeHit)
    FSM_TRANSITION_DEF(t_out_of_region, tOutofRegion)
#endif

#define FSM_GOURP_DEF
    FSM_GROUP_DEF(g_battle, gBattle)
    FSM_GROUP_DEF(g_gohome, gGoHome)
#endif

#define FSM_STATE_DEF
    FSM_STATE_DEF(s_randmove, sRandMove)
    FSM_STATE_DEF(s_movetoenemy, sMovetoEnemey)
#endif
