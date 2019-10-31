#include <string.h>
int map_name(char const* str) {
  if (strcmp(str, "output") == 0) { return 0; }
  if (strcmp(str, "size") == 0) { return 1; }
  return -1;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int predict_out_num_sizes_0(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 5; 
            classes[3] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    if (features[12] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[6] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 31; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[13] <= 2.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[6] <= -0.5) {
                                if (features[1] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                } else {
                                    if (features[1] <= 3.5) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 2; 
                                        classes[3] = 0; 
                                    }
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[1] <= 3.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_1(float features[]) {
    int classes[4];
    
    if (features[7] <= 3.5) {
        if (features[3] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 16; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[13] <= 1.0) {
                    if (features[6] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 23; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[13] <= 3.5) {
                        if (features[4] <= -0.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 6; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[10] <= -0.5) {
                    if (features[7] <= 1.0) {
                        if (features[12] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[9] <= 1.0) {
                            if (features[4] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_2(float features[]) {
    int classes[4];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[7] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 22; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[5] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[4] <= 0.5) {
                    if (features[6] <= -0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 6; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 2.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= -0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_3(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[3] <= 1.0) {
            classes[0] = 12; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[8] <= 0.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[10] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[4] <= -0.5) {
                    if (features[12] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 23; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            if (features[3] <= 2.0) {
                                if (features[12] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 5; 
                }
            }
        } else {
            classes[0] = 4; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_4(float features[]) {
    int classes[4];
    
    if (features[12] <= -0.5) {
        if (features[6] <= -0.5) {
            if (features[3] <= 3.5) {
                if (features[1] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 3.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[11] <= 1.0) {
                        if (features[8] <= -0.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 3; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 19; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 3.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 6; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_5(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 10; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 5; 
            classes[3] = 0; 
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 22; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[13] <= 0.5) {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            } else {
                if (features[9] <= 1.0) {
                    if (features[4] <= 0.5) {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[7] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 4; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_6(float features[]) {
    int classes[4];
    
    if (features[1] <= 3.5) {
        if (features[0] <= 0.5) {
            if (features[6] <= 0.0) {
                classes[0] = 14; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        } else {
            if (features[5] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 18; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[13] <= 0.5) {
                    if (features[7] <= 1.0) {
                        if (features[3] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 6; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[9] <= 1.0) {
                                if (features[4] <= 0.5) {
                                    classes[0] = 1; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 7; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.5) {
            if (features[3] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 1; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_7(float features[]) {
    int classes[4];
    
    if (features[6] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[13] <= 3.5) {
                if (features[2] <= -0.5) {
                    classes[0] = 9; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 7; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 18; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[3] <= 2.0) {
                if (features[13] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 5; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[8] <= 0.5) {
            if (features[8] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_8(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[13] <= 3.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 12; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[6] <= -0.5) {
                if (features[13] <= 0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[9] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_9(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 3; 
            classes[3] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[6] <= -0.5) {
                    if (features[4] <= -0.5) {
                        if (features[13] <= 2.0) {
                            if (features[12] <= 0.0) {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 13; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[7] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 3; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[5] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[3] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_10(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[3] <= 1.0) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[4] <= 0.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[13] <= 0.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 18; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[3] <= 3.5) {
                            if (features[6] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[7] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_11(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 21; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[12] <= 0.5) {
            if (features[9] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[2] <= 0.5) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 13; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                if (features[0] <= 0.5) {
                                    classes[0] = 2; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[7] <= 1.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        } else {
            classes[0] = 4; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_12(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[3] <= 2.0) {
            if (features[5] <= 1.0) {
                classes[0] = 18; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[5] <= 1.0) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 19; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[7] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 7; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 3.5) {
                        if (features[8] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 5; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_13(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 2.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 12; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 5; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[9] <= 1.0) {
                                if (features[4] <= 0.5) {
                                    classes[0] = 1; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                    classes[3] = 3; 
                                }
                            } else {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_14(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[1] <= 2.0) {
            if (features[5] <= 1.0) {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[4] <= -0.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 19; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        if (features[3] <= 3.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_15(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[3] <= 2.0) {
            if (features[5] <= 1.0) {
                classes[0] = 18; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 19; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[3] <= 3.5) {
                            if (features[9] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                            } else {
                                classes[0] = 4; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 6; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_16(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 9; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 3.5) {
            if (features[7] <= 1.0) {
                if (features[0] <= 0.5) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= 0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 33; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[4] <= -0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[13] <= 0.5) {
                                    if (features[1] <= 2.0) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    } else {
                                        if (features[3] <= 3.5) {
                                            classes[0] = 0; 
                                            classes[1] = 1; 
                                            classes[2] = 3; 
                                            classes[3] = 0; 
                                        } else {
                                            classes[0] = 0; 
                                            classes[1] = 0; 
                                            classes[2] = 1; 
                                            classes[3] = 0; 
                                        }
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[11] <= 1.0) {
                    if (features[8] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[1] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 4; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_17(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[7] <= 1.0) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        if (features[3] <= 2.0) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[0] <= 0.5) {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 14; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[5] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[9] <= 1.0) {
                    if (features[4] <= 0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[7] <= 1.0) {
                                if (features[1] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 7; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 4; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_18(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[12] <= -0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 20; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[3] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 29; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 5; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[8] <= -0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 4; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_19(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[6] <= 0.0) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[5] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 27; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[13] <= 1.0) {
                            if (features[4] <= -0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            } else {
                if (features[6] <= 0.5) {
                    if (features[7] <= 3.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_20(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[4] <= 0.5) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 16; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 5; 
                classes[3] = 0; 
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[7] <= 1.0) {
                    if (features[13] <= 0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                }
            } else {
                if (features[8] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_21(float features[]) {
    int classes[4];
    
    if (features[6] <= 0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[9] <= 1.0) {
                if (features[12] <= 0.5) {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 2.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 27; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[7] <= 1.0) {
                            if (features[13] <= 0.5) {
                                if (features[1] <= 3.5) {
                                    if (features[1] <= 2.0) {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    } else {
                                        if (features[2] <= 0.5) {
                                            classes[0] = 0; 
                                            classes[1] = 6; 
                                            classes[2] = 0; 
                                            classes[3] = 0; 
                                        } else {
                                            classes[0] = 0; 
                                            classes[1] = 1; 
                                            classes[2] = 4; 
                                            classes[3] = 0; 
                                        }
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[7] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 5; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_22(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[7] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        if (features[12] <= 0.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 20; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[8] <= -0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 4; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[9] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 5; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_23(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 16; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[1] <= 2.0) {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[2] <= 0.5) {
                if (features[6] <= -0.5) {
                    if (features[5] <= 1.0) {
                        if (features[13] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[0] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 13; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[7] <= 1.0) {
                    if (features[12] <= -0.5) {
                        if (features[3] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[6] <= 0.5) {
                        if (features[10] <= -0.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 6; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_24(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 12; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[13] <= 3.5) {
                if (features[2] <= -0.5) {
                    classes[0] = 13; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= 0.5) {
                        if (features[2] <= 0.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[13] <= 2.5) {
            if (features[4] <= 0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            if (features[6] <= 0.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[7] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 3; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_25(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[2] <= 0.5) {
            if (features[13] <= 0.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 13; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[7] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 12; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[13] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 12; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[11] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 3; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_26(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[2] <= -0.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 3.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[5] <= 3.5) {
            if (features[3] <= 2.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_27(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 8; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 2.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[8] <= 0.5) {
                    if (features[8] <= -0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_28(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[4] <= 0.0) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[1] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[7] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 26; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[4] <= -0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[13] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[11] <= 1.0) {
                        if (features[7] <= 3.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_29(float features[]) {
    int classes[4];
    
    if (features[6] <= -0.5) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 17; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[13] <= 3.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 16; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[12] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 8; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[8] <= 0.5) {
            if (features[1] <= 3.5) {
                if (features[10] <= -0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_30(float features[]) {
    int classes[4];
    
    if (features[6] <= -0.5) {
        if (features[2] <= -0.5) {
            classes[0] = 9; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[1] <= 2.0) {
                if (features[13] <= 0.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[13] <= 2.5) {
                    if (features[3] <= 3.5) {
                        if (features[1] <= 3.5) {
                            if (features[4] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 13; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    if (features[13] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 5; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    }
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[13] <= 3.5) {
                        if (features[5] <= 1.0) {
                            if (features[0] <= 0.5) {
                                classes[0] = 4; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[4] <= 0.5) {
            if (features[5] <= 3.5) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        } else {
            if (features[6] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_31(float features[]) {
    int classes[4];
    
    if (features[13] <= 2.5) {
        if (features[2] <= 0.5) {
            if (features[8] <= 0.0) {
                if (features[1] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[6] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[7] <= 1.0) {
                    if (features[12] <= -0.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                if (features[1] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[9] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[5] <= 1.0) {
                if (features[2] <= -0.5) {
                    classes[0] = 21; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 3; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_32(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        } else {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[5] <= 3.5) {
            if (features[9] <= 1.0) {
                if (features[6] <= -0.5) {
                    if (features[1] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 6; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[13] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            }
                        }
                    } else {
                        if (features[4] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 21; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                if (features[13] <= 2.5) {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 3; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        if (features[12] <= -0.5) {
                                            classes[0] = 0; 
                                            classes[1] = 3; 
                                            classes[2] = 4; 
                                            classes[3] = 0; 
                                        } else {
                                            classes[0] = 0; 
                                            classes[1] = 0; 
                                            classes[2] = 1; 
                                            classes[3] = 0; 
                                        }
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 4; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_33(float features[]) {
    int classes[4];
    
    if (features[13] <= 0.0) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[6] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 6; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 8; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            }
        }
    } else {
        if (features[3] <= 2.0) {
            classes[0] = 19; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[5] <= 1.0) {
                if (features[0] <= 0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_34(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[6] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 15; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 15; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[12] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[5] <= 1.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= 0.5) {
                if (features[4] <= 0.5) {
                    classes[0] = 7; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_35(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[0] <= 0.5) {
            classes[0] = 18; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[2] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 20; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[9] <= 1.5) {
                    if (features[6] <= -0.5) {
                        if (features[13] <= 0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 6; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_36(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[5] <= 1.0) {
            classes[0] = 20; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[0] <= 0.5) {
            if (features[8] <= 0.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 5; 
                classes[3] = 0; 
            }
        } else {
            if (features[3] <= 3.5) {
                if (features[13] <= 2.5) {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 3.5) {
                            if (features[12] <= -0.5) {
                                if (features[5] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 10; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 8; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 5; 
                                        classes[3] = 0; 
                                    }
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 6; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 11; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_37(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 14; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 17; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[8] <= -0.5) {
            if (features[6] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 14; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[1] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 6; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_38(float features[]) {
    int classes[4];
    
    if (features[6] <= 0.5) {
        if (features[4] <= -0.5) {
            if (features[2] <= -0.5) {
                classes[0] = 15; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 7; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[8] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                if (features[6] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 6; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 2; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 6; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 1; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_39(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 3; 
            classes[3] = 0; 
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 23; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[3] <= 3.5) {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[12] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 13; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[3] <= 3.5) {
                    if (features[9] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_40(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[3] <= 3.5) {
                        if (features[10] <= -0.5) {
                            if (features[9] <= 1.0) {
                                if (features[6] <= -0.5) {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 6; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 5; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 1; 
                                        classes[1] = 0; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 0; 
                                        classes[3] = 1; 
                                    }
                                }
                            } else {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        } else {
            if (features[1] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[3] <= 1.0) {
                        classes[0] = 14; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= -0.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 12; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 7; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_41(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[5] <= 1.0) {
            if (features[0] <= 0.5) {
                classes[0] = 15; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= 0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 20; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 7; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[13] <= 0.5) {
                    if (features[2] <= 0.5) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[7] <= 1.0) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    if (features[5] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 3; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_42(float features[]) {
    int classes[4];
    
    if (features[3] <= 0.0) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[7] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 2.0) {
                    if (features[12] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 31; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[3] <= 2.0) {
                    if (features[13] <= 1.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[4] <= -0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 7; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[6] <= 0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[9] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_43(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[6] <= -0.5) {
            if (features[4] <= -0.5) {
                if (features[12] <= 0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 13; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[0] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 8; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[3] <= 3.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[9] <= 3.5) {
                if (features[4] <= 0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 5; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_44(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[4] <= -0.5) {
            if (features[1] <= 2.0) {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 6; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[9] <= 3.5) {
                    if (features[5] <= 3.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_45(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        } else {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[12] <= 0.5) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[13] <= 1.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[6] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 1; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            if (features[12] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[13] <= 0.5) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[8] <= -0.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_46(float features[]) {
    int classes[4];
    
    if (features[1] <= 3.5) {
        if (features[5] <= 1.0) {
            if (features[2] <= -0.5) {
                classes[0] = 18; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 7; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 15; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[7] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 10; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[8] <= 0.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[7] <= 1.0) {
                    if (features[1] <= 2.0) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[8] <= -0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[3] <= 3.5) {
            classes[0] = 0; 
            classes[1] = 3; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_47(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 10; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 3; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[13] <= 0.0) {
                classes[0] = 0; 
                classes[1] = 15; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 13; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[1] <= 2.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 13; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[9] <= 1.0) {
                    if (features[4] <= 0.5) {
                        if (features[13] <= 0.5) {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_48(float features[]) {
    int classes[4];
    
    if (features[5] <= 3.5) {
        if (features[5] <= 1.0) {
            if (features[12] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[13] <= 3.5) {
                    if (features[13] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 18; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[10] <= -0.5) {
                if (features[6] <= -0.5) {
                    if (features[3] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 5; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 5; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_49(float features[]) {
    int classes[4];
    
    if (features[7] <= 3.5) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 20; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[13] <= 3.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[13] <= 0.5) {
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[9] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[13] <= 2.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[8] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 6; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_50(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[5] <= 1.0) {
            classes[0] = 20; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 1.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[8] <= 0.5) {
            if (features[7] <= 1.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 18; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 8; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[6] <= 0.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    if (features[10] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 5; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_51(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 9; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[10] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 15; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[5] <= 3.5) {
                    if (features[7] <= 1.0) {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 2.0) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[13] <= 2.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        } else {
            classes[0] = 4; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_52(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[1] <= 3.5) {
            if (features[3] <= 2.0) {
                classes[0] = 17; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 6; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[11] <= 1.0) {
            if (features[4] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            } else {
                if (features[6] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_53(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[12] <= -0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            classes[0] = 21; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[12] <= -0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 10; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[6] <= 0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 7; 
                        }
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    }
                }
            }
        } else {
            if (features[13] <= 2.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 11; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_54(float features[]) {
    int classes[4];
    
    if (features[7] <= 3.5) {
        if (features[2] <= 0.5) {
            if (features[0] <= 0.5) {
                classes[0] = 11; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= 0.5) {
                    if (features[7] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 38; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 9; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[1] <= 3.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 3; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_55(float features[]) {
    int classes[4];
    
    if (features[12] <= -0.5) {
        if (features[6] <= -0.5) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 3.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[10] <= -0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[6] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                } else {
                    if (features[9] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 22; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 13; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[13] <= 2.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_56(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[4] <= 0.0) {
            classes[0] = 19; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[6] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[12] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 25; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 9; 
                    classes[3] = 0; 
                }
            } else {
                if (features[5] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 5; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_57(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 10; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 17; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 2.5) {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 9; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[7] <= 3.5) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    if (features[10] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 5; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_58(float features[]) {
    int classes[4];
    
    if (features[1] <= 3.5) {
        if (features[2] <= -0.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[6] <= -0.5) {
                if (features[4] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[12] <= 0.5) {
                            if (features[12] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[0] <= 0.5) {
                                    classes[0] = 1; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 8; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[13] <= 2.5) {
                            if (features[12] <= -0.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 6; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[9] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 1; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 6; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_59(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[4] <= 0.0) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[7] <= 1.0) {
                if (features[13] <= 2.5) {
                    if (features[1] <= 2.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 13; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                if (features[12] <= -0.5) {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 7; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 2; 
                                        classes[3] = 0; 
                                    }
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[13] <= 3.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        } else {
            if (features[5] <= 3.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_60(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[2] <= -0.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[12] <= 0.5) {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 14; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 3.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[2] <= 0.5) {
                if (features[13] <= 1.0) {
                    if (features[9] <= 1.5) {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[13] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 8; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_61(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 5; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                } else {
                    if (features[7] <= 3.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 4; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_62(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 7; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= 0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 12; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        if (features[3] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 11; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[8] <= 0.5) {
                if (features[8] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 6; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_63(float features[]) {
    int classes[4];
    
    if (features[6] <= -0.5) {
        if (features[3] <= 0.0) {
            classes[0] = 12; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[4] <= -0.5) {
                if (features[13] <= 2.0) {
                    if (features[13] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[3] <= 3.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[6] <= 0.5) {
            if (features[4] <= 0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[11] <= 1.0) {
                    if (features[7] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_64(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        } else {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[1] <= 2.0) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[7] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 23; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[4] <= -0.5) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[8] <= -0.5) {
                    if (features[3] <= 3.5) {
                        if (features[1] <= 2.0) {
                            if (features[12] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[12] <= -0.5) {
                                if (features[6] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_65(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 11; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[8] <= 0.0) {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[13] <= 0.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 34; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        } else {
            if (features[10] <= -0.5) {
                if (features[6] <= -0.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 1.0) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    } else {
                        if (features[3] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_66(float features[]) {
    int classes[4];
    
    if (features[13] <= 2.5) {
        if (features[9] <= 1.0) {
            if (features[6] <= -0.5) {
                if (features[12] <= 0.5) {
                    if (features[4] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[3] <= 3.5) {
                                    if (features[2] <= 0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 3; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 4; 
                                        classes[2] = 7; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 4; 
            }
        }
    } else {
        if (features[2] <= -0.5) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 3.5) {
                if (features[1] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_67(float features[]) {
    int classes[4];
    
    if (features[3] <= 0.0) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[12] <= 0.5) {
            if (features[7] <= 3.5) {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= -0.5) {
                            if (features[1] <= 3.5) {
                                if (features[0] <= 0.5) {
                                    classes[0] = 2; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[4] <= 0.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[6] <= -0.5) {
                                if (features[1] <= 2.0) {
                                    if (features[12] <= -0.5) {
                                        classes[0] = 0; 
                                        classes[1] = 4; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 8; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 4; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[8] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 4; 
                }
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_68(float features[]) {
    int classes[4];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[2] <= -0.5) {
                classes[0] = 14; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[1] <= 3.5) {
                        if (features[9] <= 1.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[4] <= 0.5) {
                                    classes[0] = 2; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 3; 
                                }
                            }
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 7; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_69(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[12] <= -0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[4] <= -0.5) {
                classes[0] = 17; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[7] <= 1.5) {
                if (features[5] <= 1.0) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[13] <= 0.5) {
                    if (features[6] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 8; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_70(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[4] <= -0.5) {
            classes[0] = 21; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[13] <= 1.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[0] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 14; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[6] <= -0.5) {
                        if (features[13] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    }
                }
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[5] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 5; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_71(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[6] <= 0.0) {
            classes[0] = 18; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 6; 
            classes[3] = 0; 
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[12] <= 0.5) {
                if (features[3] <= 3.5) {
                    if (features[5] <= 1.0) {
                        if (features[13] <= 1.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 8; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 2.0) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 4; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[9] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_72(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 19; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[7] <= 3.5) {
                if (features[6] <= -0.5) {
                    if (features[12] <= 0.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 25; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 15; 
                    classes[3] = 0; 
                }
            } else {
                if (features[7] <= 3.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[8] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_73(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[2] <= 0.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[5] <= 1.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 21; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[13] <= 2.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[12] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 9; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            } else {
                if (features[8] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_74(float features[]) {
    int classes[4];
    
    if (features[13] <= 0.0) {
        if (features[3] <= 3.5) {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[8] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 4; 
        }
    } else {
        if (features[2] <= -0.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[1] <= 2.0) {
                if (features[13] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_75(float features[]) {
    int classes[4];
    
    if (features[6] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[3] <= 2.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 25; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                }
            }
        }
    } else {
        if (features[9] <= 3.5) {
            if (features[1] <= 3.5) {
                if (features[10] <= -0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_76(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[2] <= -0.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[13] <= 2.0) {
                    if (features[12] <= 0.0) {
                        if (features[3] <= 2.0) {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[4] <= 0.5) {
            if (features[13] <= 0.5) {
                if (features[5] <= 3.5) {
                    if (features[2] <= 0.5) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[8] <= -0.5) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 8; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[11] <= 1.0) {
                if (features[5] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 4; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_77(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[3] <= 2.0) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[12] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    } else {
        if (features[10] <= -0.5) {
            if (features[6] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[13] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 10; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_78(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 7; 
            classes[3] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[3] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 20; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[13] <= 0.5) {
                        if (features[6] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_79(float features[]) {
    int classes[4];
    
    if (features[8] <= 0.5) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 13; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[4] <= 0.5) {
                    if (features[13] <= 2.5) {
                        if (features[12] <= -0.5) {
                            if (features[2] <= 0.5) {
                                if (features[7] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 3; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[1] <= 3.5) {
                                    if (features[1] <= 2.0) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 3; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 7; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[7] <= 3.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 4; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_80(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[13] <= 2.5) {
            if (features[4] <= -0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[9] <= 1.0) {
                        if (features[6] <= -0.5) {
                            if (features[12] <= -0.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 9; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 4; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 3; 
                            }
                        }
                    } else {
                        if (features[6] <= 0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                            }
                        }
                    }
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_81(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[2] <= -0.5) {
            classes[0] = 12; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 17; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[13] <= 0.5) {
                if (features[1] <= 3.5) {
                    if (features[6] <= -0.5) {
                        if (features[3] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 5; 
                            }
                        }
                    }
                } else {
                    if (features[5] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_82(float features[]) {
    int classes[4];
    
    if (features[13] <= 0.0) {
        if (features[5] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 17; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[6] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[4] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[11] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 16; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            }
        } else {
            if (features[13] <= 3.5) {
                if (features[4] <= -0.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_83(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 21; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[9] <= 3.5) {
            if (features[6] <= -0.5) {
                if (features[1] <= 3.5) {
                    if (features[13] <= 2.5) {
                        if (features[1] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                if (features[13] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 4; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 4; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_84(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[8] <= 0.0) {
                if (features[7] <= 1.0) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 26; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        } else {
            if (features[3] <= 2.0) {
                if (features[13] <= 1.0) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[6] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[1] <= 3.5) {
                            if (features[8] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 3; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_85(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 6; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[0] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[9] <= 3.5) {
                if (features[9] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            if (features[2] <= 0.5) {
                                if (features[12] <= -0.5) {
                                    if (features[7] <= 1.0) {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 3; 
                                        classes[1] = 0; 
                                        classes[2] = 0; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                if (features[13] <= 0.5) {
                                    if (features[1] <= 3.5) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 5; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 1; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 4; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_86(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[7] <= 1.0) {
            if (features[0] <= 0.5) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    if (features[1] <= 2.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 33; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        if (features[13] <= 1.0) {
                            if (features[5] <= 1.0) {
                                classes[0] = 5; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 3.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 3; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_87(float features[]) {
    int classes[4];
    
    if (features[3] <= 0.0) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[3] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 18; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 3.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[13] <= 2.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[9] <= 1.5) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[7] <= 3.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_88(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                if (features[13] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 9; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[4] <= -0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 20; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 11; 
                    classes[3] = 0; 
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
                classes[3] = 0; 
            } else {
                if (features[3] <= 3.5) {
                    classes[0] = 8; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_89(float features[]) {
    int classes[4];
    
    if (features[4] <= -0.5) {
        if (features[3] <= 2.0) {
            classes[0] = 14; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 25; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[4] <= 0.5) {
            if (features[7] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[13] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 8; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 7; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[6] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
                classes[3] = 5; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_90(float features[]) {
    int classes[4];
    
    if (features[13] <= 2.5) {
        if (features[6] <= 0.5) {
            if (features[2] <= 0.5) {
                if (features[7] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                if (features[7] <= 1.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[8] <= -0.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                }
            }
        } else {
            if (features[3] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 6; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
            }
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[5] <= 1.0) {
                classes[0] = 18; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 5; 
                classes[3] = 0; 
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_91(float features[]) {
    int classes[4];
    
    if (features[3] <= 0.0) {
        classes[0] = 9; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[8] <= 0.0) {
                if (features[6] <= -0.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 29; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 5; 
                classes[3] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[6] <= -0.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 8; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                }
            } else {
                if (features[4] <= 0.5) {
                    if (features[6] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_92(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[6] <= 0.0) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 3; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 28; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[6] <= -0.5) {
                if (features[12] <= -0.5) {
                    if (features[1] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 7; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[1] <= 2.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[4] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[11] <= 1.0) {
                        if (features[5] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 3; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 2; 
                        }
                    } else {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_93(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[6] <= -0.5) {
            if (features[3] <= 2.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[13] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[13] <= 2.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[5] <= 1.0) {
                        if (features[0] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 3.5) {
                if (features[4] <= 0.5) {
                    classes[0] = 11; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[11] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[3] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_94(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[0] <= 0.5) {
            if (features[5] <= 1.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
                classes[3] = 0; 
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[12] <= -0.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[4] <= -0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[12] <= -0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                if (features[4] <= 0.5) {
                                    if (features[2] <= 0.5) {
                                        if (features[6] <= -0.5) {
                                            classes[0] = 0; 
                                            classes[1] = 5; 
                                            classes[2] = 0; 
                                            classes[3] = 0; 
                                        } else {
                                            classes[0] = 1; 
                                            classes[1] = 0; 
                                            classes[2] = 0; 
                                            classes[3] = 0; 
                                        }
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 4; 
                                        classes[3] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        }
                    } else {
                        if (features[13] <= 2.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                if (features[10] <= -0.5) {
                    if (features[6] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_95(float features[]) {
    int classes[4];
    
    if (features[7] <= 1.0) {
        if (features[0] <= 0.5) {
            classes[0] = 14; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[1] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 7; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 15; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                        }
                    }
                }
            }
        }
    } else {
        if (features[8] <= 0.5) {
            if (features[3] <= 3.5) {
                if (features[10] <= -0.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_96(float features[]) {
    int classes[4];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 2; 
            classes[3] = 0; 
        } else {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[3] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 28; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[4] <= -0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    if (features[13] <= 0.5) {
                        if (features[7] <= 1.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                            }
                        } else {
                            if (features[6] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                    }
                } else {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 3; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_97(float features[]) {
    int classes[4];
    
    if (features[9] <= 3.5) {
        if (features[2] <= -0.5) {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[6] <= -0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        if (features[2] <= 0.5) {
                            if (features[12] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 19; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            if (features[12] <= -0.5) {
                                if (features[3] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                } else {
                                    if (features[1] <= 3.5) {
                                        classes[0] = 0; 
                                        classes[1] = 1; 
                                        classes[2] = 3; 
                                        classes[3] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 0; 
                                        classes[2] = 3; 
                                        classes[3] = 0; 
                                    }
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                            }
                        }
                    }
                }
            } else {
                if (features[9] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        }
                    }
                } else {
                    if (features[10] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 6; 
        classes[3] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_98(float features[]) {
    int classes[4];
    
    if (features[2] <= -0.5) {
        classes[0] = 10; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
    } else {
        if (features[13] <= 2.5) {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 3; 
                    classes[3] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        if (features[13] <= 0.0) {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[7] <= 1.0) {
                    if (features[3] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                        }
                    }
                } else {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                    } else {
                        if (features[11] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 1; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    }
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[13] <= 3.5) {
                    if (features[5] <= 1.0) {
                        if (features[0] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 17; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_sizes_99(float features[]) {
    int classes[4];
    
    if (features[3] <= 2.0) {
        if (features[5] <= 1.0) {
            classes[0] = 22; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
        } else {
            if (features[12] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 1; 
                classes[3] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
            }
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[13] <= 2.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 14; 
                classes[2] = 0; 
                classes[3] = 0; 
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[3] <= 3.5) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                }
            } else {
                if (features[8] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 4; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 4; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_num_sizes (float features[]) {
    int n_classes = 4;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_num_sizes_0(features)]++;
    classes[predict_out_num_sizes_1(features)]++;
    classes[predict_out_num_sizes_2(features)]++;
    classes[predict_out_num_sizes_3(features)]++;
    classes[predict_out_num_sizes_4(features)]++;
    classes[predict_out_num_sizes_5(features)]++;
    classes[predict_out_num_sizes_6(features)]++;
    classes[predict_out_num_sizes_7(features)]++;
    classes[predict_out_num_sizes_8(features)]++;
    classes[predict_out_num_sizes_9(features)]++;
    classes[predict_out_num_sizes_10(features)]++;
    classes[predict_out_num_sizes_11(features)]++;
    classes[predict_out_num_sizes_12(features)]++;
    classes[predict_out_num_sizes_13(features)]++;
    classes[predict_out_num_sizes_14(features)]++;
    classes[predict_out_num_sizes_15(features)]++;
    classes[predict_out_num_sizes_16(features)]++;
    classes[predict_out_num_sizes_17(features)]++;
    classes[predict_out_num_sizes_18(features)]++;
    classes[predict_out_num_sizes_19(features)]++;
    classes[predict_out_num_sizes_20(features)]++;
    classes[predict_out_num_sizes_21(features)]++;
    classes[predict_out_num_sizes_22(features)]++;
    classes[predict_out_num_sizes_23(features)]++;
    classes[predict_out_num_sizes_24(features)]++;
    classes[predict_out_num_sizes_25(features)]++;
    classes[predict_out_num_sizes_26(features)]++;
    classes[predict_out_num_sizes_27(features)]++;
    classes[predict_out_num_sizes_28(features)]++;
    classes[predict_out_num_sizes_29(features)]++;
    classes[predict_out_num_sizes_30(features)]++;
    classes[predict_out_num_sizes_31(features)]++;
    classes[predict_out_num_sizes_32(features)]++;
    classes[predict_out_num_sizes_33(features)]++;
    classes[predict_out_num_sizes_34(features)]++;
    classes[predict_out_num_sizes_35(features)]++;
    classes[predict_out_num_sizes_36(features)]++;
    classes[predict_out_num_sizes_37(features)]++;
    classes[predict_out_num_sizes_38(features)]++;
    classes[predict_out_num_sizes_39(features)]++;
    classes[predict_out_num_sizes_40(features)]++;
    classes[predict_out_num_sizes_41(features)]++;
    classes[predict_out_num_sizes_42(features)]++;
    classes[predict_out_num_sizes_43(features)]++;
    classes[predict_out_num_sizes_44(features)]++;
    classes[predict_out_num_sizes_45(features)]++;
    classes[predict_out_num_sizes_46(features)]++;
    classes[predict_out_num_sizes_47(features)]++;
    classes[predict_out_num_sizes_48(features)]++;
    classes[predict_out_num_sizes_49(features)]++;
    classes[predict_out_num_sizes_50(features)]++;
    classes[predict_out_num_sizes_51(features)]++;
    classes[predict_out_num_sizes_52(features)]++;
    classes[predict_out_num_sizes_53(features)]++;
    classes[predict_out_num_sizes_54(features)]++;
    classes[predict_out_num_sizes_55(features)]++;
    classes[predict_out_num_sizes_56(features)]++;
    classes[predict_out_num_sizes_57(features)]++;
    classes[predict_out_num_sizes_58(features)]++;
    classes[predict_out_num_sizes_59(features)]++;
    classes[predict_out_num_sizes_60(features)]++;
    classes[predict_out_num_sizes_61(features)]++;
    classes[predict_out_num_sizes_62(features)]++;
    classes[predict_out_num_sizes_63(features)]++;
    classes[predict_out_num_sizes_64(features)]++;
    classes[predict_out_num_sizes_65(features)]++;
    classes[predict_out_num_sizes_66(features)]++;
    classes[predict_out_num_sizes_67(features)]++;
    classes[predict_out_num_sizes_68(features)]++;
    classes[predict_out_num_sizes_69(features)]++;
    classes[predict_out_num_sizes_70(features)]++;
    classes[predict_out_num_sizes_71(features)]++;
    classes[predict_out_num_sizes_72(features)]++;
    classes[predict_out_num_sizes_73(features)]++;
    classes[predict_out_num_sizes_74(features)]++;
    classes[predict_out_num_sizes_75(features)]++;
    classes[predict_out_num_sizes_76(features)]++;
    classes[predict_out_num_sizes_77(features)]++;
    classes[predict_out_num_sizes_78(features)]++;
    classes[predict_out_num_sizes_79(features)]++;
    classes[predict_out_num_sizes_80(features)]++;
    classes[predict_out_num_sizes_81(features)]++;
    classes[predict_out_num_sizes_82(features)]++;
    classes[predict_out_num_sizes_83(features)]++;
    classes[predict_out_num_sizes_84(features)]++;
    classes[predict_out_num_sizes_85(features)]++;
    classes[predict_out_num_sizes_86(features)]++;
    classes[predict_out_num_sizes_87(features)]++;
    classes[predict_out_num_sizes_88(features)]++;
    classes[predict_out_num_sizes_89(features)]++;
    classes[predict_out_num_sizes_90(features)]++;
    classes[predict_out_num_sizes_91(features)]++;
    classes[predict_out_num_sizes_92(features)]++;
    classes[predict_out_num_sizes_93(features)]++;
    classes[predict_out_num_sizes_94(features)]++;
    classes[predict_out_num_sizes_95(features)]++;
    classes[predict_out_num_sizes_96(features)]++;
    classes[predict_out_num_sizes_97(features)]++;
    classes[predict_out_num_sizes_98(features)]++;
    classes[predict_out_num_sizes_99(features)]++;

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

static int predict_out_num_outputs_0(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[9] <= 1.0) {
            if (features[1] <= 2.0) {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 16; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 10; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 39; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_1(float features[]) {
    int classes[3];
    
    if (features[7] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 3; 
                        classes[1] = 13; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 29; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 15; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_2(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 4; 
            classes[2] = 0; 
        } else {
            if (features[7] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 12; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 34; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_3(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[0] <= 0.5) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[1] <= 3.5) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[4] <= 0.5) {
                if (features[13] <= 0.5) {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 14; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 8; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_4(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[5] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                classes[0] = 1; 
                classes[1] = 7; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 28; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_5(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[2] <= -0.5) {
            classes[0] = 7; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[1] <= 2.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 4; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 3; 
                classes[1] = 1; 
                classes[2] = 0; 
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[12] <= -0.5) {
                    if (features[7] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_6(float features[]) {
    int classes[3];
    
    if (features[1] <= 2.0) {
        if (features[4] <= -0.5) {
            if (features[12] <= 0.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[4] <= -0.5) {
            if (features[1] <= 3.5) {
                if (features[12] <= -0.5) {
                    classes[0] = 1; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 23; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_7(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[13] <= 0.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 27; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[13] <= 0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 2; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 13; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_8(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                classes[0] = 3; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 22; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[13] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    if (features[6] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 8; 
                                classes[2] = 4; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 6; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_9(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[4] <= -0.5) {
                classes[0] = 3; 
                classes[1] = 7; 
                classes[2] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 1; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_10(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[1] <= 2.0) {
            if (features[13] <= 0.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[12] <= -0.5) {
                classes[0] = 2; 
                classes[1] = 8; 
                classes[2] = 0; 
            } else {
                classes[0] = 25; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[9] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 11; 
                    classes[2] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 1; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 5; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_11(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            if (features[4] <= -0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 10; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 18; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 39; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_12(float features[]) {
    int classes[3];
    
    if (features[9] <= 1.0) {
        if (features[5] <= 1.0) {
            if (features[2] <= -0.5) {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 19; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 2.0) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 2; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 12; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_13(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[12] <= -0.5) {
            if (features[6] <= -0.5) {
                if (features[4] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 1; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                            }
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 18; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_14(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[4] <= -0.5) {
            if (features[1] <= 3.5) {
                if (features[12] <= -0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 12; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[7] <= 1.0) {
                    if (features[12] <= -0.5) {
                        if (features[1] <= 2.0) {
                            classes[0] = 1; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 10; 
                                    classes[2] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 2; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    } else {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_15(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[6] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 4; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 19; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 35; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_16(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 2; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 33; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 16; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_17(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[1] <= 3.5) {
            if (features[13] <= 0.0) {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 32; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[13] <= 1.5) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 13; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_18(float features[]) {
    int classes[3];
    
    if (features[3] <= 0.0) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[12] <= -0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 17; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[1] <= 2.0) {
                    if (features[12] <= -0.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[6] <= -0.5) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_19(float features[]) {
    int classes[3];
    
    if (features[0] <= 0.5) {
        if (features[6] <= 0.0) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 2; 
            classes[2] = 0; 
        }
    } else {
        if (features[13] <= 0.0) {
            if (features[8] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 3; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[1] <= 3.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 4; 
                                    classes[2] = 1; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 21; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_20(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[2] <= 0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 16; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 5; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 11; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 1; 
            classes[2] = 0; 
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[12] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 16; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_21(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[1] <= 3.5) {
                if (features[4] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 37; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 10; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_22(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[1] <= 3.5) {
            if (features[3] <= 2.0) {
                if (features[0] <= 0.5) {
                    classes[0] = 15; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[13] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[12] <= -0.5) {
            if (features[7] <= 1.0) {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 17; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_23(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[1] <= 3.5) {
            if (features[3] <= 0.0) {
                classes[0] = 16; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 5; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 17; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 1; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 16; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_24(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                classes[0] = 3; 
                classes[1] = 9; 
                classes[2] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[1] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 40; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_25(float features[]) {
    int classes[3];
    
    if (features[9] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[7] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 33; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 9; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_26(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 2.0) {
            classes[0] = 1; 
            classes[1] = 1; 
            classes[2] = 0; 
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 1; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 22; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 44; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_27(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[6] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 2; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 14; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 12; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 30; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_28(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 15; 
            classes[2] = 0; 
        } else {
            if (features[4] <= 0.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    if (features[7] <= 1.0) {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 2; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 40; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_29(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[4] <= -0.5) {
            if (features[3] <= 0.0) {
                classes[0] = 12; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 10; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 24; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        if (features[3] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 3; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 12; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_30(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                if (features[5] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 31; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 11; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_31(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[2] <= 0.5) {
            if (features[4] <= -0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 11; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 38; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_32(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[2] <= 0.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 2; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 37; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 13; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_33(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[4] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 15; 
                classes[2] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        if (features[3] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 1; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_34(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[1] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[7] <= 1.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 40; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_35(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[4] <= -0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 13; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[7] <= 1.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 3; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 38; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_36(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[0] <= 0.5) {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[12] <= -0.5) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 15; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 1; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 13; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_37(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 7; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 31; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[8] <= -0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                } else {
                    if (features[3] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 3; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 9; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_38(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[13] <= 0.5) {
            if (features[2] <= 0.5) {
                if (features[4] <= -0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 3; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 34; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 15; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_39(float features[]) {
    int classes[3];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 3; 
            classes[2] = 0; 
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 1; 
                        classes[1] = 11; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 10; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[13] <= 0.5) {
                        if (features[1] <= 3.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 15; 
                                classes[2] = 1; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_40(float features[]) {
    int classes[3];
    
    if (features[9] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 2; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 37; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 11; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_41(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 2; 
                    }
                }
            }
        } else {
            classes[0] = 38; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 13; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_42(float features[]) {
    int classes[3];
    
    if (features[7] <= 1.0) {
        if (features[4] <= -0.5) {
            if (features[2] <= -0.5) {
                classes[0] = 14; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    if (features[1] <= 2.0) {
                        if (features[13] <= 0.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 4; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[12] <= -0.5) {
                            classes[0] = 3; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 10; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                if (features[13] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 10; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 7; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 11; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_43(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[2] <= -0.5) {
            classes[0] = 13; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 0.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 13; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[12] <= -0.5) {
                classes[0] = 1; 
                classes[1] = 4; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 20; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_44(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.5) {
        if (features[4] <= -0.5) {
            classes[0] = 0; 
            classes[1] = 10; 
            classes[2] = 0; 
        } else {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 24; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 39; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_45(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 32; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[5] <= 3.5) {
                if (features[8] <= -0.5) {
                    if (features[2] <= 0.5) {
                        if (features[7] <= 1.0) {
                            if (features[3] <= 2.0) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 2; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 5; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_46(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[12] <= -0.5) {
            if (features[3] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[5] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                    }
                }
            }
        } else {
            classes[0] = 38; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 0; 
        classes[1] = 10; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_47(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            if (features[7] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 3; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_48(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            classes[0] = 0; 
            classes[1] = 10; 
            classes[2] = 0; 
        } else {
            classes[0] = 32; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[4] <= 0.5) {
                if (features[8] <= -0.5) {
                    if (features[7] <= 1.0) {
                        if (features[1] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 10; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 12; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_49(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[8] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            } else {
                if (features[7] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 9; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_50(float features[]) {
    int classes[3];
    
    if (features[3] <= 2.0) {
        if (features[5] <= 1.0) {
            if (features[13] <= 0.0) {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
            } else {
                classes[0] = 16; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 4; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[13] <= 1.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 10; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 16; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_51(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[2] <= 0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
            } else {
                if (features[4] <= 0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[8] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 2; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_52(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 34; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 15; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_53(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[6] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 3; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 14; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_54(float features[]) {
    int classes[3];
    
    if (features[7] <= 1.0) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 12; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[12] <= -0.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[12] <= -0.5) {
                    if (features[1] <= 3.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 5; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 17; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 10; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_55(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[6] <= -0.5) {
            if (features[4] <= -0.5) {
                classes[0] = 2; 
                classes[1] = 6; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 3; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 11; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 43; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_56(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 4; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 12; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 44; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_57(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 10; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[13] <= 0.0) {
            if (features[8] <= -0.5) {
                if (features[4] <= 0.5) {
                    if (features[6] <= -0.5) {
                        if (features[3] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 2; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                if (features[4] <= -0.5) {
                                    if (features[1] <= 3.5) {
                                        classes[0] = 3; 
                                        classes[1] = 12; 
                                        classes[2] = 0; 
                                    } else {
                                        classes[0] = 0; 
                                        classes[1] = 2; 
                                        classes[2] = 0; 
                                    }
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 5; 
                                    classes[2] = 0; 
                                }
                            } else {
                                if (features[3] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 5; 
                                    classes[2] = 2; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_58(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[8] <= -0.5) {
            if (features[7] <= 1.0) {
                if (features[4] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 10; 
                    classes[2] = 0; 
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 11; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 35; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_59(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[10] <= -0.5) {
            if (features[8] <= -0.5) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            classes[0] = 5; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 16; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 1; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 34; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_60(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[12] <= -0.5) {
            classes[0] = 3; 
            classes[1] = 11; 
            classes[2] = 0; 
        } else {
            classes[0] = 32; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[4] <= 0.5) {
            if (features[13] <= 0.5) {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 1; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 5; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_61(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 15; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 13; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 15; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_62(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 20; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[4] <= 0.5) {
                if (features[6] <= -0.5) {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[1] <= 3.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 3; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 8; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_63(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[7] <= 1.0) {
                    if (features[1] <= 3.5) {
                        if (features[4] <= -0.5) {
                            classes[0] = 1; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 6; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 2; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 9; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_64(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[2] <= 0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 38; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[13] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_65(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 11; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 0.5) {
                    if (features[6] <= -0.5) {
                        if (features[5] <= 1.0) {
                            if (features[1] <= 3.5) {
                                classes[0] = 1; 
                                classes[1] = 15; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[1] <= 2.0) {
                if (features[4] <= -0.5) {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[11] <= 1.0) {
                    if (features[8] <= -0.5) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 2; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_66(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[9] <= 1.0) {
            if (features[6] <= -0.5) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            classes[0] = 2; 
                            classes[1] = 7; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 10; 
                                classes[2] = 1; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 6; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 32; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_67(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[2] <= 0.5) {
            if (features[5] <= 1.0) {
                classes[0] = 0; 
                classes[1] = 6; 
                classes[2] = 0; 
            } else {
                if (features[8] <= 0.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[8] <= -0.5) {
                if (features[1] <= 2.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[7] <= 1.0) {
                        if (features[3] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 1; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 36; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_68(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                classes[0] = 1; 
                classes[1] = 9; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 27; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[8] <= -0.5) {
            if (features[13] <= 0.5) {
                if (features[7] <= 1.0) {
                    if (features[1] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 1; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 7; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 8; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_69(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[6] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    }
                }
            }
        }
    } else {
        classes[0] = 36; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_70(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[7] <= 1.0) {
            if (features[5] <= 1.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 15; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 36; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_71(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 35; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 33; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_72(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[1] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[4] <= -0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 1; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                if (features[9] <= 1.0) {
                    if (features[6] <= -0.5) {
                        if (features[1] <= 3.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 6; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 1; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 39; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_73(float features[]) {
    int classes[3];
    
    if (features[3] <= 0.0) {
        classes[0] = 13; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[7] <= 1.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 14; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 21; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
            }
        } else {
            if (features[9] <= 1.0) {
                if (features[13] <= 0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            if (features[6] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 9; 
                                classes[2] = 1; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_74(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 40; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 29; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_75(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            if (features[4] <= 0.5) {
                if (features[4] <= -0.5) {
                    classes[0] = 2; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                } else {
                    if (features[6] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 3; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 10; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 36; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_76(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[3] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 30; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    if (features[4] <= 0.5) {
                        if (features[6] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 3; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_77(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[3] <= 0.0) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[3] <= 2.0) {
                if (features[12] <= 0.0) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[13] <= 0.5) {
            if (features[1] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                if (features[9] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 11; 
                                classes[2] = 2; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 2; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_78(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 2; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 31; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[12] <= -0.5) {
            if (features[5] <= 3.5) {
                if (features[7] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        if (features[3] <= 3.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 1; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 8; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 6; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_79(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[5] <= 1.0) {
            if (features[2] <= -0.5) {
                classes[0] = 12; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[13] <= 1.0) {
                    if (features[1] <= 3.5) {
                        classes[0] = 3; 
                        classes[1] = 8; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 15; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_80(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[1] <= 3.5) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 5; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[4] <= -0.5) {
                                classes[0] = 1; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 9; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    if (features[12] <= -0.5) {
                        if (features[3] <= 2.0) {
                            if (features[5] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 1; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 6; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 15; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_81(float features[]) {
    int classes[3];
    
    if (features[6] <= -0.5) {
        if (features[2] <= -0.5) {
            classes[0] = 12; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[3] <= 2.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[13] <= 1.0) {
                        classes[0] = 2; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[3] <= 3.5) {
                    if (features[13] <= 0.5) {
                        if (features[2] <= 0.5) {
                            if (features[5] <= 1.0) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 1; 
                                    classes[1] = 7; 
                                    classes[2] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 11; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 19; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_82(float features[]) {
    int classes[3];
    
    if (features[13] <= 0.0) {
        if (features[5] <= 1.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 1; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 13; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 1; 
                classes[1] = 2; 
                classes[2] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 2; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 38; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_83(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[1] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[5] <= 1.0) {
                classes[0] = 2; 
                classes[1] = 6; 
                classes[2] = 0; 
            } else {
                if (features[6] <= -0.5) {
                    if (features[3] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 15; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_84(float features[]) {
    int classes[3];
    
    if (features[2] <= -0.5) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[12] <= -0.5) {
            if (features[8] <= -0.5) {
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 2; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 2; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 7; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 27; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_85(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[12] <= -0.5) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                if (features[1] <= 3.5) {
                    classes[0] = 5; 
                    classes[1] = 8; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            }
        } else {
            classes[0] = 31; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[8] <= -0.5) {
            if (features[4] <= 0.5) {
                if (features[12] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 1; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 4; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 6; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_86(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[1] <= 2.0) {
            if (features[13] <= 0.0) {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            } else {
                classes[0] = 6; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[1] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 17; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 5; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 10; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[13] <= 1.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[2] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                classes[0] = 1; 
                classes[1] = 1; 
                classes[2] = 0; 
            }
        } else {
            if (features[13] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 15; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_87(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[3] <= 2.0) {
            classes[0] = 19; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[1] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 7; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[6] <= -0.5) {
            if (features[3] <= 2.0) {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[13] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 15; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_88(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[1] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[6] <= -0.5) {
                    if (features[4] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 1; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                }
            } else {
                if (features[6] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 1; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        classes[0] = 37; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_89(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[3] <= 2.0) {
            classes[0] = 14; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[12] <= -0.5) {
                if (features[1] <= 3.5) {
                    classes[0] = 3; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 15; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[4] <= 0.5) {
            if (features[12] <= -0.5) {
                if (features[8] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        if (features[6] <= -0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 7; 
                                classes[2] = 2; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 6; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 9; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_90(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[6] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 2; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 11; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 15; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 40; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_91(float features[]) {
    int classes[3];
    
    if (features[3] <= 2.0) {
        if (features[2] <= 0.5) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[4] <= -0.5) {
                if (features[13] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            } else {
                if (features[13] <= 1.0) {
                    classes[0] = 1; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[9] <= 1.5) {
                if (features[5] <= 1.0) {
                    if (features[12] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 12; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[6] <= -0.5) {
                        if (features[12] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 6; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[9] <= 1.0) {
                    if (features[4] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 8; 
                        classes[2] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_92(float features[]) {
    int classes[3];
    
    if (features[4] <= -0.5) {
        if (features[12] <= -0.5) {
            classes[0] = 0; 
            classes[1] = 15; 
            classes[2] = 0; 
        } else {
            classes[0] = 28; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[3] <= 2.0) {
            if (features[13] <= 1.0) {
                classes[0] = 1; 
                classes[1] = 3; 
                classes[2] = 0; 
            } else {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[8] <= -0.5) {
                    if (features[6] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 7; 
                            classes[2] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 3; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_93(float features[]) {
    int classes[3];
    
    if (features[7] <= 1.0) {
        if (features[4] <= -0.5) {
            if (features[12] <= -0.5) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 26; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 9; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 17; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_94(float features[]) {
    int classes[3];
    
    if (features[5] <= 1.0) {
        if (features[0] <= 0.5) {
            classes[0] = 21; 
            classes[1] = 0; 
            classes[2] = 0; 
        } else {
            if (features[13] <= 0.0) {
                if (features[2] <= 0.5) {
                    classes[0] = 2; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                }
            } else {
                classes[0] = 13; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[12] <= -0.5) {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[1] <= 3.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 3; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 8; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 10; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_95(float features[]) {
    int classes[3];
    
    if (features[12] <= -0.5) {
        if (features[4] <= 0.5) {
            if (features[7] <= 1.0) {
                if (features[1] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 3; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 1; 
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 8; 
            classes[2] = 0; 
        }
    } else {
        classes[0] = 42; 
        classes[1] = 0; 
        classes[2] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_96(float features[]) {
    int classes[3];
    
    if (features[0] <= 0.5) {
        if (features[13] <= 1.0) {
            classes[0] = 0; 
            classes[1] = 2; 
            classes[2] = 0; 
        } else {
            classes[0] = 15; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[2] <= 0.5) {
            if (features[3] <= 2.0) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    if (features[12] <= -0.5) {
                        if (features[1] <= 3.5) {
                            classes[0] = 4; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 9; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            }
        } else {
            if (features[12] <= -0.5) {
                if (features[1] <= 2.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[9] <= 1.0) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 1; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_97(float features[]) {
    int classes[3];
    
    if (features[3] <= 0.0) {
        classes[0] = 8; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[12] <= -0.5) {
            if (features[6] <= -0.5) {
                if (features[3] <= 2.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[1] <= 3.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 2; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 9; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 24; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_98(float features[]) {
    int classes[3];
    
    if (features[2] <= 0.5) {
        if (features[13] <= 0.0) {
            classes[0] = 0; 
            classes[1] = 16; 
            classes[2] = 0; 
        } else {
            classes[0] = 38; 
            classes[1] = 0; 
            classes[2] = 0; 
        }
    } else {
        if (features[7] <= 1.0) {
            if (features[12] <= -0.5) {
                classes[0] = 0; 
                classes[1] = 14; 
                classes[2] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 4; 
            classes[2] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_outputs_99(float features[]) {
    int classes[3];
    
    if (features[3] <= 0.0) {
        classes[0] = 15; 
        classes[1] = 0; 
        classes[2] = 0; 
    } else {
        if (features[5] <= 1.0) {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 7; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 13; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                }
            } else {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                } else {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[2] <= 0.5) {
                    if (features[13] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[13] <= 0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 1; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                            }
                        } else {
                            classes[0] = 5; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
                classes[2] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 3; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_num_outputs (float features[]) {
    int n_classes = 3;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_num_outputs_0(features)]++;
    classes[predict_out_num_outputs_1(features)]++;
    classes[predict_out_num_outputs_2(features)]++;
    classes[predict_out_num_outputs_3(features)]++;
    classes[predict_out_num_outputs_4(features)]++;
    classes[predict_out_num_outputs_5(features)]++;
    classes[predict_out_num_outputs_6(features)]++;
    classes[predict_out_num_outputs_7(features)]++;
    classes[predict_out_num_outputs_8(features)]++;
    classes[predict_out_num_outputs_9(features)]++;
    classes[predict_out_num_outputs_10(features)]++;
    classes[predict_out_num_outputs_11(features)]++;
    classes[predict_out_num_outputs_12(features)]++;
    classes[predict_out_num_outputs_13(features)]++;
    classes[predict_out_num_outputs_14(features)]++;
    classes[predict_out_num_outputs_15(features)]++;
    classes[predict_out_num_outputs_16(features)]++;
    classes[predict_out_num_outputs_17(features)]++;
    classes[predict_out_num_outputs_18(features)]++;
    classes[predict_out_num_outputs_19(features)]++;
    classes[predict_out_num_outputs_20(features)]++;
    classes[predict_out_num_outputs_21(features)]++;
    classes[predict_out_num_outputs_22(features)]++;
    classes[predict_out_num_outputs_23(features)]++;
    classes[predict_out_num_outputs_24(features)]++;
    classes[predict_out_num_outputs_25(features)]++;
    classes[predict_out_num_outputs_26(features)]++;
    classes[predict_out_num_outputs_27(features)]++;
    classes[predict_out_num_outputs_28(features)]++;
    classes[predict_out_num_outputs_29(features)]++;
    classes[predict_out_num_outputs_30(features)]++;
    classes[predict_out_num_outputs_31(features)]++;
    classes[predict_out_num_outputs_32(features)]++;
    classes[predict_out_num_outputs_33(features)]++;
    classes[predict_out_num_outputs_34(features)]++;
    classes[predict_out_num_outputs_35(features)]++;
    classes[predict_out_num_outputs_36(features)]++;
    classes[predict_out_num_outputs_37(features)]++;
    classes[predict_out_num_outputs_38(features)]++;
    classes[predict_out_num_outputs_39(features)]++;
    classes[predict_out_num_outputs_40(features)]++;
    classes[predict_out_num_outputs_41(features)]++;
    classes[predict_out_num_outputs_42(features)]++;
    classes[predict_out_num_outputs_43(features)]++;
    classes[predict_out_num_outputs_44(features)]++;
    classes[predict_out_num_outputs_45(features)]++;
    classes[predict_out_num_outputs_46(features)]++;
    classes[predict_out_num_outputs_47(features)]++;
    classes[predict_out_num_outputs_48(features)]++;
    classes[predict_out_num_outputs_49(features)]++;
    classes[predict_out_num_outputs_50(features)]++;
    classes[predict_out_num_outputs_51(features)]++;
    classes[predict_out_num_outputs_52(features)]++;
    classes[predict_out_num_outputs_53(features)]++;
    classes[predict_out_num_outputs_54(features)]++;
    classes[predict_out_num_outputs_55(features)]++;
    classes[predict_out_num_outputs_56(features)]++;
    classes[predict_out_num_outputs_57(features)]++;
    classes[predict_out_num_outputs_58(features)]++;
    classes[predict_out_num_outputs_59(features)]++;
    classes[predict_out_num_outputs_60(features)]++;
    classes[predict_out_num_outputs_61(features)]++;
    classes[predict_out_num_outputs_62(features)]++;
    classes[predict_out_num_outputs_63(features)]++;
    classes[predict_out_num_outputs_64(features)]++;
    classes[predict_out_num_outputs_65(features)]++;
    classes[predict_out_num_outputs_66(features)]++;
    classes[predict_out_num_outputs_67(features)]++;
    classes[predict_out_num_outputs_68(features)]++;
    classes[predict_out_num_outputs_69(features)]++;
    classes[predict_out_num_outputs_70(features)]++;
    classes[predict_out_num_outputs_71(features)]++;
    classes[predict_out_num_outputs_72(features)]++;
    classes[predict_out_num_outputs_73(features)]++;
    classes[predict_out_num_outputs_74(features)]++;
    classes[predict_out_num_outputs_75(features)]++;
    classes[predict_out_num_outputs_76(features)]++;
    classes[predict_out_num_outputs_77(features)]++;
    classes[predict_out_num_outputs_78(features)]++;
    classes[predict_out_num_outputs_79(features)]++;
    classes[predict_out_num_outputs_80(features)]++;
    classes[predict_out_num_outputs_81(features)]++;
    classes[predict_out_num_outputs_82(features)]++;
    classes[predict_out_num_outputs_83(features)]++;
    classes[predict_out_num_outputs_84(features)]++;
    classes[predict_out_num_outputs_85(features)]++;
    classes[predict_out_num_outputs_86(features)]++;
    classes[predict_out_num_outputs_87(features)]++;
    classes[predict_out_num_outputs_88(features)]++;
    classes[predict_out_num_outputs_89(features)]++;
    classes[predict_out_num_outputs_90(features)]++;
    classes[predict_out_num_outputs_91(features)]++;
    classes[predict_out_num_outputs_92(features)]++;
    classes[predict_out_num_outputs_93(features)]++;
    classes[predict_out_num_outputs_94(features)]++;
    classes[predict_out_num_outputs_95(features)]++;
    classes[predict_out_num_outputs_96(features)]++;
    classes[predict_out_num_outputs_97(features)]++;
    classes[predict_out_num_outputs_98(features)]++;
    classes[predict_out_num_outputs_99(features)]++;

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
