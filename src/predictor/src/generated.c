#include <string.h>
int map_name(char const* str) {
  if (strcmp(str, "output") == 0) { return 0; }
  if (strcmp(str, "size") == 0) { return 1; }
  return -1;
}
char const* keys[] = {
  "param_0_pointers",
  "param_0_type",
  "param_1_pointers",
  "param_1_type",
  "param_2_pointers",
  "param_2_type",
  "param_3_pointers",
  "param_3_type",
  "param_4_pointers",
  "param_4_type",
  "param_5_pointers",
  "param_5_type",
  "return_pointers",
  "return_type"
};
int n_keys=14;
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int predict_out_uses_output_0(float features[]) {
    int classes[2];
    
    if (features[4] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 6; 
                classes[1] = 5; 
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
            }
        } else {
            classes[0] = 22; 
            classes[1] = 0; 
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 2; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                }
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[3] <= 3.5) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 15; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_1(float features[]) {
    int classes[2];
    
    if (features[6] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 10; 
                classes[1] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 6; 
                        classes[1] = 4; 
                    } else {
                        classes[0] = 14; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 4; 
                        classes[1] = 3; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                    }
                } else {
                    classes[0] = 6; 
                    classes[1] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 10; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_2(float features[]) {
    int classes[2];
    
    if (features[7] <= 1.0) {
        if (features[0] <= 0.5) {
            if (features[3] <= 1.0) {
                classes[0] = 5; 
                classes[1] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 3; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[2] <= 0.5) {
                            if (features[4] <= -0.5) {
                                classes[0] = 4; 
                                classes[1] = 6; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                    }
                }
            } else {
                classes[0] = 23; 
                classes[1] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 15; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_3(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[7] <= 1.0) {
            if (features[5] <= 1.0) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 4; 
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 4; 
                    classes[1] = 2; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 16; 
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_4(float features[]) {
    int classes[2];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
            } else {
                classes[0] = 7; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 27; 
            classes[1] = 0; 
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 3; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 20; 
            }
        } else {
            classes[0] = 7; 
            classes[1] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_5(float features[]) {
    int classes[2];
    
    if (features[4] <= 0.5) {
        if (features[5] <= 1.0) {
            if (features[12] <= -0.5) {
                classes[0] = 3; 
                classes[1] = 10; 
            } else {
                classes[0] = 24; 
                classes[1] = 0; 
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 3; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                }
            } else {
                classes[0] = 6; 
                classes[1] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 10; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_6(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 1; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[2] <= 0.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 5; 
                        classes[1] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
            }
        }
    } else {
        classes[0] = 30; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_7(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[8] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 1; 
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[1] <= 3.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 4; 
                            classes[1] = 5; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 4; 
        }
    } else {
        classes[0] = 38; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_8(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[4] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 5; 
                classes[1] = 6; 
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 21; 
        }
    } else {
        classes[0] = 34; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_9(float features[]) {
    int classes[2];
    
    if (features[6] <= -0.5) {
        if (features[4] <= -0.5) {
            if (features[0] <= 0.5) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                } else {
                    classes[0] = 8; 
                    classes[1] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 6; 
                } else {
                    classes[0] = 16; 
                    classes[1] = 0; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 14; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_10(float features[]) {
    int classes[2];
    
    if (features[6] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[4] <= -0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 9; 
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 2; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                }
            }
        } else {
            classes[0] = 36; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 11; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_11(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[7] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 6; 
                        classes[1] = 6; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 11; 
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_12(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 2; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 5; 
                            classes[1] = 4; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 11; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
            }
        }
    } else {
        classes[0] = 26; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_13(float features[]) {
    int classes[2];
    
    if (features[7] <= 1.0) {
        if (features[5] <= 1.0) {
            if (features[13] <= 0.0) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 3; 
                }
            } else {
                classes[0] = 29; 
                classes[1] = 0; 
            }
        } else {
            if (features[1] <= 2.0) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 5; 
                        classes[1] = 2; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                }
            } else {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 7; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 12; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_14(float features[]) {
    int classes[2];
    
    if (features[6] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 9; 
            classes[1] = 0; 
        } else {
            if (features[2] <= 0.5) {
                if (features[5] <= 1.0) {
                    if (features[13] <= 0.0) {
                        classes[0] = 5; 
                        classes[1] = 4; 
                    } else {
                        classes[0] = 15; 
                        classes[1] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                    }
                }
            } else {
                if (features[13] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                    }
                } else {
                    classes[0] = 9; 
                    classes[1] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 13; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_15(float features[]) {
    int classes[2];
    
    if (features[1] <= 2.0) {
        classes[0] = 11; 
        classes[1] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[1] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 9; 
                    classes[1] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 4; 
                        classes[1] = 5; 
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 11; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_16(float features[]) {
    int classes[2];
    
    if (features[3] <= 2.0) {
        if (features[0] <= 0.5) {
            classes[0] = 4; 
            classes[1] = 0; 
        } else {
            if (features[4] <= -0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                } else {
                    if (features[13] <= 1.0) {
                        classes[0] = 2; 
                        classes[1] = 2; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[13] <= 1.0) {
                if (features[6] <= -0.5) {
                    if (features[5] <= 1.0) {
                        if (features[0] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 7; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 11; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                }
            } else {
                classes[0] = 13; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 11; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_17(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[5] <= 1.0) {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 2; 
            } else {
                classes[0] = 3; 
                classes[1] = 3; 
            }
        } else {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 22; 
            }
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_18(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 4; 
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 5; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 15; 
            }
        }
    } else {
        classes[0] = 28; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_uses_output_19(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 2; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[5] <= 1.0) {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
            }
        }
    } else {
        classes[0] = 34; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_uses_output (float features[]) {
    int n_classes = 2;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_uses_output_0(features)]++;
    classes[predict_out_uses_output_1(features)]++;
    classes[predict_out_uses_output_2(features)]++;
    classes[predict_out_uses_output_3(features)]++;
    classes[predict_out_uses_output_4(features)]++;
    classes[predict_out_uses_output_5(features)]++;
    classes[predict_out_uses_output_6(features)]++;
    classes[predict_out_uses_output_7(features)]++;
    classes[predict_out_uses_output_8(features)]++;
    classes[predict_out_uses_output_9(features)]++;
    classes[predict_out_uses_output_10(features)]++;
    classes[predict_out_uses_output_11(features)]++;
    classes[predict_out_uses_output_12(features)]++;
    classes[predict_out_uses_output_13(features)]++;
    classes[predict_out_uses_output_14(features)]++;
    classes[predict_out_uses_output_15(features)]++;
    classes[predict_out_uses_output_16(features)]++;
    classes[predict_out_uses_output_17(features)]++;
    classes[predict_out_uses_output_18(features)]++;
    classes[predict_out_uses_output_19(features)]++;

    int class_idx = 0;
    int class_val = classes[0];
    for (i = 1; i < n_classes; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int predict_out_output_0_arg_0(float features[]) {
    int classes[6];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 5; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 24; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[13] <= 0.0) {
                classes[0] = 1; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 2; 
            } else {
                if (features[6] <= 0.5) {
                    if (features[12] <= -0.5) {
                        if (features[11] <= 1.0) {
                            if (features[5] <= 3.5) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 12; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                    classes[5] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_1(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[4] <= 0.5) {
            if (features[7] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    if (features[6] <= -0.5) {
                        if (features[3] <= 2.0) {
                            if (features[5] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
                classes[5] = 0; 
            }
        } else {
            if (features[9] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 1; 
            }
        }
    } else {
        classes[0] = 42; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_2(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 11; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[10] <= -0.5) {
                if (features[7] <= 3.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[8] <= -0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                if (features[4] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            }
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[9] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 3; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 1; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        }
    } else {
        classes[0] = 31; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_3(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[4] <= 0.5) {
            if (features[1] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[5] <= 3.5) {
                            if (features[7] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                if (features[9] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 2; 
                            classes[5] = 0; 
                        }
                    }
                }
            }
        } else {
            if (features[8] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 4; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 2; 
            }
        }
    } else {
        classes[0] = 30; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_4(float features[]) {
    int classes[6];
    
    if (features[6] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[4] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 31; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 1; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[6] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[10] <= -0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 3; 
                classes[5] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_5(float features[]) {
    int classes[6];
    
    if (features[8] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[4] <= 0.5) {
                if (features[2] <= 0.5) {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[6] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 2; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 34; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[6] <= 0.5) {
            if (features[4] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[10] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 2; 
            classes[5] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_6(float features[]) {
    int classes[6];
    
    if (features[4] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[0] <= 0.5) {
                classes[0] = 9; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[12] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 12; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        } else {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        }
    } else {
        if (features[13] <= 1.0) {
            if (features[9] <= 1.0) {
                if (features[4] <= 0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 2; 
                } else {
                    if (features[1] <= 3.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 4; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[6] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 1; 
                            classes[5] = 0; 
                        }
                    }
                }
            }
        } else {
            classes[0] = 7; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_7(float features[]) {
    int classes[6];
    
    if (features[4] <= -0.5) {
        if (features[3] <= 1.0) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        } else {
            if (features[0] <= 0.5) {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 1; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[12] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            if (features[8] <= 0.5) {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[4] <= 0.5) {
                        if (features[3] <= 3.5) {
                            if (features[7] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                if (features[9] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            }
                        } else {
                            if (features[9] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 1; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        if (features[10] <= -0.5) {
                            if (features[5] <= 3.5) {
                                if (features[8] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_8(float features[]) {
    int classes[6];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            classes[0] = 26; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[12] <= -0.5) {
            if (features[4] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[9] <= 1.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 1; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                if (features[6] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 6; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 2; 
                    classes[5] = 0; 
                }
            } else {
                if (features[5] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 4; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_9(float features[]) {
    int classes[6];
    
    if (features[7] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[1] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[4] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            if (features[5] <= 1.0) {
                                classes[0] = 4; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                }
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            classes[0] = 33; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[4] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 1; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                    classes[5] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_10(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 1; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[6] <= 0.5) {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[7] <= 1.0) {
                            if (features[4] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            if (features[4] <= 0.5) {
                                if (features[8] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        if (features[8] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
                classes[5] = 0; 
            }
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_11(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[8] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[7] <= 1.0) {
                            if (features[0] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                if (features[5] <= 1.0) {
                                    classes[0] = 2; 
                                    classes[1] = 8; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 2; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[7] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 1; 
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 4; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        }
    } else {
        classes[0] = 27; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_12(float features[]) {
    int classes[6];
    
    if (features[9] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[4] <= 0.5) {
                if (features[2] <= 0.5) {
                    if (features[7] <= 1.0) {
                        if (features[3] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[4] <= -0.5) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 2; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 6; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 39; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        if (features[10] <= -0.5) {
            if (features[3] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 1; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_13(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[9] <= 3.5) {
            if (features[4] <= 0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[9] <= 1.0) {
                            if (features[1] <= 3.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 7; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 1; 
                                classes[5] = 0; 
                            }
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 6; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 4; 
        }
    } else {
        classes[0] = 27; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_14(float features[]) {
    int classes[6];
    
    if (features[13] <= 0.0) {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
            classes[5] = 1; 
        } else {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[7] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        if (features[5] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 1; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    if (features[1] <= 3.5) {
                        if (features[10] <= -0.5) {
                            if (features[9] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_15(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[9] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 3; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[6] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 1; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[8] <= 0.5) {
                if (features[3] <= 3.5) {
                    if (features[11] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 2; 
            }
        }
    } else {
        classes[0] = 39; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_16(float features[]) {
    int classes[6];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 3.5) {
            if (features[7] <= 1.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    if (features[4] <= 0.5) {
                        if (features[8] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 2; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= 0.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 1; 
                classes[5] = 0; 
            }
        }
    } else {
        classes[0] = 31; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_17(float features[]) {
    int classes[6];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[8] <= -0.5) {
                    if (features[4] <= -0.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 6; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        }
    } else {
        classes[0] = 31; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_18(float features[]) {
    int classes[6];
    
    if (features[13] <= 0.0) {
        if (features[10] <= -0.5) {
            if (features[9] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            if (features[6] <= -0.5) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 1; 
                                    classes[1] = 15; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
                classes[5] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 1; 
            classes[4] = 0; 
            classes[5] = 0; 
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_0_arg_19(float features[]) {
    int classes[6];
    
    if (features[13] <= 0.0) {
        if (features[2] <= 0.5) {
            if (features[4] <= -0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 5; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            }
        } else {
            if (features[7] <= 3.5) {
                if (features[9] <= 1.0) {
                    if (features[3] <= 3.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                            classes[5] = 0; 
                        } else {
                            if (features[4] <= 0.5) {
                                if (features[1] <= 2.0) {
                                    classes[0] = 1; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                    classes[5] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                                classes[5] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                        classes[5] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                    classes[4] = 0; 
                    classes[5] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
                classes[5] = 0; 
            }
        }
    } else {
        classes[0] = 38; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
        classes[5] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 6; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_output_0_arg (float features[]) {
    int n_classes = 6;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_output_0_arg_0(features)]++;
    classes[predict_out_output_0_arg_1(features)]++;
    classes[predict_out_output_0_arg_2(features)]++;
    classes[predict_out_output_0_arg_3(features)]++;
    classes[predict_out_output_0_arg_4(features)]++;
    classes[predict_out_output_0_arg_5(features)]++;
    classes[predict_out_output_0_arg_6(features)]++;
    classes[predict_out_output_0_arg_7(features)]++;
    classes[predict_out_output_0_arg_8(features)]++;
    classes[predict_out_output_0_arg_9(features)]++;
    classes[predict_out_output_0_arg_10(features)]++;
    classes[predict_out_output_0_arg_11(features)]++;
    classes[predict_out_output_0_arg_12(features)]++;
    classes[predict_out_output_0_arg_13(features)]++;
    classes[predict_out_output_0_arg_14(features)]++;
    classes[predict_out_output_0_arg_15(features)]++;
    classes[predict_out_output_0_arg_16(features)]++;
    classes[predict_out_output_0_arg_17(features)]++;
    classes[predict_out_output_0_arg_18(features)]++;
    classes[predict_out_output_0_arg_19(features)]++;

    int class_idx = 0;
    int class_val = classes[0];
    for (i = 1; i < n_classes; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int predict_out_output_1_arg_0(float features[]) {
    int classes[2];
    
    if (features[4] <= -0.5) {
        classes[0] = 37; 
        classes[1] = 0; 
    } else {
        if (features[2] <= 0.5) {
            classes[0] = 10; 
            classes[1] = 0; 
        } else {
            if (features[9] <= 1.0) {
                if (features[7] <= 1.0) {
                    if (features[12] <= -0.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 5; 
                                classes[1] = 1; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 5; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_1(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_2(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_3(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_4(float features[]) {
    int classes[2];
    
    if (features[2] <= 0.5) {
        classes[0] = 40; 
        classes[1] = 0; 
    } else {
        if (features[9] <= 1.0) {
            if (features[7] <= 1.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                        } else {
                            classes[0] = 5; 
                            classes[1] = 1; 
                        }
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                    }
                }
            } else {
                classes[0] = 5; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_5(float features[]) {
    int classes[2];
    
    if (features[5] <= 1.0) {
        classes[0] = 38; 
        classes[1] = 0; 
    } else {
        if (features[5] <= 3.5) {
            if (features[4] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                } else {
                    if (features[7] <= 1.0) {
                        if (features[13] <= 0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 4; 
                                classes[1] = 0; 
                            } else {
                                classes[0] = 2; 
                                classes[1] = 1; 
                            }
                        } else {
                            classes[0] = 7; 
                            classes[1] = 0; 
                        }
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 3; 
            classes[1] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_6(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_7(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_8(float features[]) {
    int classes[2];
    
    if (features[4] <= -0.5) {
        classes[0] = 35; 
        classes[1] = 0; 
    } else {
        if (features[8] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 7; 
                classes[1] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    if (features[13] <= 0.5) {
                        if (features[7] <= 1.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                            } else {
                                classes[0] = 8; 
                                classes[1] = 1; 
                            }
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                }
            }
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_9(float features[]) {
    int classes[2];
    
    if (features[7] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[1] <= 3.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 10; 
                        classes[1] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 5; 
                            classes[1] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 33; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 10; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_10(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            classes[0] = 15; 
            classes[1] = 0; 
        } else {
            if (features[7] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                    } else {
                        if (features[3] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 4; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 8; 
                classes[1] = 0; 
            }
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_11(float features[]) {
    int classes[2];
    
    if (features[12] <= -0.5) {
        if (features[8] <= -0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 12; 
                classes[1] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 9; 
                    classes[1] = 0; 
                } else {
                    if (features[6] <= -0.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 1; 
                        }
                    } else {
                        classes[0] = 7; 
                        classes[1] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 9; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 27; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_12(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_13(float features[]) {
    int classes[2];
    
    if (features[2] <= 0.5) {
        classes[0] = 40; 
        classes[1] = 0; 
    } else {
        if (features[7] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 8; 
                classes[1] = 0; 
            } else {
                if (features[3] <= 3.5) {
                    if (features[13] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 1; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                }
            }
        } else {
            classes[0] = 11; 
            classes[1] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_14(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 3.5) {
            if (features[2] <= 0.5) {
                classes[0] = 14; 
                classes[1] = 0; 
            } else {
                if (features[8] <= -0.5) {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 2.0) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 1; 
                        }
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                }
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_15(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_16(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 3.5) {
            if (features[7] <= 1.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                        } else {
                            classes[0] = 6; 
                            classes[1] = 4; 
                        }
                    }
                }
            } else {
                classes[0] = 9; 
                classes[1] = 0; 
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 31; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_17(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_18(float features[]) {
    int classes[2];
    
    if (features[13] <= 0.0) {
        if (features[7] <= 1.0) {
            if (features[0] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 7; 
                    classes[1] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 13; 
                        classes[1] = 0; 
                    } else {
                        classes[0] = 6; 
                        classes[1] = 1; 
                    }
                }
            }
        } else {
            classes[0] = 7; 
            classes[1] = 0; 
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_output_1_arg_19(float features[]) {
    int classes[2];
    
    classes[0] = 68; 
    classes[1] = 0; 
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 2; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_output_1_arg (float features[]) {
    int n_classes = 2;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_output_1_arg_0(features)]++;
    classes[predict_out_output_1_arg_1(features)]++;
    classes[predict_out_output_1_arg_2(features)]++;
    classes[predict_out_output_1_arg_3(features)]++;
    classes[predict_out_output_1_arg_4(features)]++;
    classes[predict_out_output_1_arg_5(features)]++;
    classes[predict_out_output_1_arg_6(features)]++;
    classes[predict_out_output_1_arg_7(features)]++;
    classes[predict_out_output_1_arg_8(features)]++;
    classes[predict_out_output_1_arg_9(features)]++;
    classes[predict_out_output_1_arg_10(features)]++;
    classes[predict_out_output_1_arg_11(features)]++;
    classes[predict_out_output_1_arg_12(features)]++;
    classes[predict_out_output_1_arg_13(features)]++;
    classes[predict_out_output_1_arg_14(features)]++;
    classes[predict_out_output_1_arg_15(features)]++;
    classes[predict_out_output_1_arg_16(features)]++;
    classes[predict_out_output_1_arg_17(features)]++;
    classes[predict_out_output_1_arg_18(features)]++;
    classes[predict_out_output_1_arg_19(features)]++;

    int class_idx = 0;
    int class_val = classes[0];
    for (i = 1; i < n_classes; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}
