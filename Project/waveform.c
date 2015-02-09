float waveform[] =
//{1.0,0.9910526315789474,0.9559398496240601,0.8990225563909774,0.820751879699248,0.7275939849624059,0.6284962406015037,0.5281954887218046,0.4288721804511278,0.33406015037593983,0.2464661654135338,0.1681954887218045,0.10233082706766918,0.04887218045112782,0.00669172932330827,-0.02458646616541353,-0.042706766917293235,-0.05390977443609023,-0.05894736842105262,-0.059624060150375933,-0.05601503759398496,-0.05323308270676692,-0.05090225563909774,-0.046315789473684206,-0.039022556390977445,-0.029624060150375938,-0.020225563909774435,-0.010300751879699246,-0.0004511278195488722,0.008721804511278195,0.016766917293233083,0.017894736842105262,0.013533834586466164,0.012180451127819547,0.011278195488721804,0.008270676691729323,0.002330827067669173,0.0006766917293233082,0.003233082706766917,0.005263157894736842,0.005714285714285714,0.005714285714285714,0.006165413533834586,0.005714285714285714,0.006165413533834586,0.00669172932330827,0.00669172932330827,0.00781954887218045,0.010977443609022555,0.013984962406015038,0.0156390977443609,0.016766917293233083,0.0156390977443609,0.012406015037593985,0.008496240601503759,0.0045864661654135335,-0.0006766917293233082,-0.005037593984962406,-0.00593984962406015,-0.005263157894736842,-0.003909774436090225,-0.0002255639097744361,0.005037593984962406,0.010075187969924812,0.012406015037593985,0.01330827067669173,0.013082706766917293,0.010977443609022555,0.007593984962406015,0.002556390977443609,-0.002030075187969925,-0.005037593984962406,-0.005488721804511277,-0.007593984962406015,-0.009849624060150376,-0.009849624060150376,-0.009849624060150376,-0.012406015037593985,-0.017894736842105262,-0.021804511278195486,-0.021804511278195486,-0.019022556390977444,-0.016541353383458645,-0.010977443609022555,-0.0004511278195488722,0.014661654135338344,0.026165413533834586,0.030751879699248117,0.029398496240601504,0.02526315789473684,0.020451127819548873,0.011954887218045112,0.002030075187969925,-0.0006766917293233082,0.0034586466165413532,0.013984962406015038,0.027293233082706765,0.035338345864661655,0.03488721804511278,0.030526315789473683,0.02458646616541353,0.014210526315789472,0.0006766917293233082,-0.01631578947368421,-0.038345864661654135,-0.06060150375939849,-0.08263157894736842,-0.10849624060150376,-0.1351127819548872,-0.15556390977443607,-0.16909774436090225,-0.17,-0.15187969924812028,-0.12210526315789473,-0.08766917293233083,-0.04541353383458647,0.0004511278195488722,0.04684210526315789,0.09661654135338346,0.1450375939849624,0.1762406015037594,0.1845112781954887,0.17345864661654134,0.13924812030075187,0.08240601503759397,0.007593984962406015,-0.08533834586466166,-0.19894736842105262,-0.3248872180451128,-0.45180451127819543,-0.5724812030075188,-0.6793984962406014,-0.7613533834586466,-0.8159398496240602,-0.8510526315789473,-0.8705263157894736,-0.8691729323308269,-0.8471428571428572,-0.8060902255639097,-0.7418045112781955,-0.657593984962406,-0.5685714285714286,-0.4839097744360902,-0.40541353383458645,-0.3354887218045113,-0.27466165413533833,-0.22345864661654133,-0.17872180451127817,-0.138796992481203,-0.10669172932330825,-0.08330827067669172,-0.06541353383458645,-0.04954887218045113,-0.038345864661654135,-0.021353383458646617,0.010075187969924812,0.05992481203007518,0.13172932330827067,0.2244360902255639,0.3350375939849624,0.45796992481203,0.5857894736842104,0.708796992481203,0.8161654135338345,0.9042857142857142,0.9664661654135337,0.9983458646616542};
{0.0,0.06279051952931337,0.12533323356430426,0.1873813145857246,0.2486898871648548,0.3090169943749474,0.3681245526846779,0.4257792915650727,0.4817536741017153,0.5358267949789967,0.5877852522924731,0.6374239897486896,0.6845471059286886,0.7289686274214116,0.7705132427757893,0.8090169943749475,0.8443279255020151,0.8763066800438637,0.9048270524660196,0.9297764858882513,0.9510565162951535,0.9685831611286311,0.9822872507286886,0.9921147013144779,0.9980267284282716,1.0,0.9980267284282716,0.9921147013144778,0.9822872507286886,0.9685831611286312,0.9510565162951536,0.9297764858882513,0.9048270524660195,0.8763066800438635,0.844327925502015,0.8090169943749475,0.7705132427757893,0.7289686274214114,0.6845471059286888,0.6374239897486899,0.5877852522924732,0.535826794978997,0.4817536741017156,0.4257792915650729,0.36812455268467814,0.3090169943749475,0.24868988716485482,0.18738131458572502,0.12533323356430454,0.06279051952931358,1.2246467991473532e-16,-0.06279051952931335,-0.12533323356430429,-0.18738131458572477,-0.24868988716485502,-0.30901699437494773,-0.3681245526846783,-0.42577929156507227,-0.481753674101715,-0.5358267949789964,-0.587785252292473,-0.6374239897486896,-0.6845471059286887,-0.7289686274214113,-0.7705132427757894,-0.8090169943749473,-0.8443279255020153,-0.8763066800438636,-0.9048270524660198,-0.9297764858882511,-0.9510565162951535,-0.968583161128631,-0.9822872507286887,-0.9921147013144778,-0.9980267284282716,-1.0,-0.9980267284282716,-0.9921147013144779,-0.9822872507286887,-0.9685831611286311,-0.9510565162951536,-0.9297764858882512,-0.9048270524660199,-0.8763066800438638,-0.8443279255020155,-0.8090169943749476,-0.7705132427757896,-0.7289686274214116,-0.684547105928689,-0.6374239897486896,-0.5877852522924734,-0.5358267949789963,-0.4817536741017153,-0.4257792915650722,-0.3681245526846787,-0.3090169943749476,-0.24868988716485535,-0.18738131458572468,-0.12533323356430465,-0.06279051952931326};

