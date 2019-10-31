#include <string.h>
int map_name(char const* str) {
  if (strcmp(str, "output") == 0) { return 0; }
  if (strcmp(str, "size") == 0) { return 1; }
  return -1;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int predict_out_num_props_0(float features[]) {
    int classes[5];
    
    if (features[13] <= 0.0) {
        if (features[5] <= 3.5) {
            if (features[9] <= 1.0) {
                if (features[3] <= 3.5) {
                    if (features[5] <= 1.0) {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            if (features[7] <= 1.0) {
                                if (features[1] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 9; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 1; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                    classes[4] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        } else {
            if (features[8] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 3; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 5; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[12] <= 0.5) {
            if (features[4] <= -0.5) {
                if (features[2] <= -0.5) {
                    classes[0] = 14; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[2] <= 0.5) {
                        if (features[13] <= 3.5) {
                            if (features[0] <= 0.5) {
                                classes[0] = 1; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 11; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            classes[0] = 3; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_1(float features[]) {
    int classes[5];
    
    if (features[7] <= 3.5) {
        if (features[3] <= 0.0) {
            classes[0] = 10; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[6] <= -0.5) {
                if (features[13] <= 2.5) {
                    if (features[2] <= 0.5) {
                        if (features[13] <= 0.0) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                if (features[5] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 15; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[4] <= -0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                if (features[12] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 2; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                                classes[4] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        if (features[1] <= 3.5) {
                            if (features[4] <= -0.5) {
                                if (features[0] <= 0.5) {
                                    classes[0] = 2; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 6; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[5] <= 1.0) {
                            classes[0] = 3; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                }
            } else {
                if (features[11] <= 1.0) {
                    if (features[9] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 1; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    } else {
        if (features[1] <= 3.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 4; 
            classes[4] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 2; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_2(float features[]) {
    int classes[5];
    
    if (features[12] <= -0.5) {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 4; 
            classes[4] = 0; 
        } else {
            if (features[7] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 12; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 2.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 4; 
                            classes[4] = 1; 
                        }
                    }
                }
            } else {
                if (features[4] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 12; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_3(float features[]) {
    int classes[5];
    
    if (features[0] <= 0.5) {
        if (features[3] <= 1.0) {
            classes[0] = 12; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[8] <= 0.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[12] <= -0.5) {
            if (features[7] <= 1.0) {
                if (features[2] <= 0.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 5; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 4; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                            }
                        }
                    }
                }
            } else {
                if (features[5] <= 3.5) {
                    if (features[9] <= 1.0) {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 3; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 2; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[13] <= 1.5) {
                    classes[0] = 1; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 17; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[4] <= -0.5) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_4(float features[]) {
    int classes[5];
    
    if (features[13] <= 2.5) {
        if (features[6] <= -0.5) {
            if (features[5] <= 1.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 6; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[3] <= 3.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 8; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 1; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[7] <= 3.5) {
                if (features[11] <= 1.0) {
                    if (features[9] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 3; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 4; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 17; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[4] <= -0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 2; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 7; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_5(float features[]) {
    int classes[5];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 10; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 5; 
            classes[4] = 0; 
        }
    } else {
        if (features[5] <= 3.5) {
            if (features[9] <= 1.0) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[12] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[6] <= -0.5) {
                        if (features[2] <= 0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[12] <= -0.5) {
                                if (features[3] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 4; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 4; 
                                    classes[4] = 1; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 4; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_6(float features[]) {
    int classes[5];
    
    if (features[1] <= 3.5) {
        if (features[0] <= 0.5) {
            if (features[6] <= 0.0) {
                classes[0] = 14; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
                classes[4] = 0; 
            }
        } else {
            if (features[5] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[13] <= 0.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 4; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 8; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[12] <= -0.5) {
                    if (features[6] <= -0.5) {
                        if (features[2] <= 0.5) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 4; 
                                classes[4] = 0; 
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[8] <= -0.5) {
                                if (features[4] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[13] <= 2.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                }
            }
        }
    } else {
        if (features[3] <= 3.5) {
            if (features[13] <= 1.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 4; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        } else {
            if (features[5] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 3; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_7(float features[]) {
    int classes[5];
    
    if (features[4] <= 0.5) {
        if (features[5] <= 1.0) {
            if (features[13] <= 0.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 9; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 12; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 15; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[3] <= 2.0) {
                    if (features[13] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[12] <= -0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 6; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 3; 
                            classes[4] = 2; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[5] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                }
            }
        }
    } else {
        if (features[0] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
            classes[4] = 0; 
        } else {
            if (features[1] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
                classes[4] = 3; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 1; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_8(float features[]) {
    int classes[5];
    
    if (features[4] <= -0.5) {
        if (features[13] <= 0.0) {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 3; 
                classes[2] = 8; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        } else {
            if (features[13] <= 3.5) {
                if (features[12] <= 0.5) {
                    if (features[3] <= 1.0) {
                        classes[0] = 10; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 3; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[8] <= 0.5) {
            if (features[7] <= 3.5) {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        if (features[7] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[6] <= -0.5) {
                                if (features[1] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 5; 
                                    classes[3] = 3; 
                                    classes[4] = 4; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                }
                            } else {
                                if (features[4] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                    classes[4] = 1; 
                                }
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 3; 
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 3; 
            classes[4] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_9(float features[]) {
    int classes[5];
    
    if (features[0] <= 0.5) {
        if (features[5] <= 1.5) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 3; 
            classes[4] = 0; 
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[2] <= 0.5) {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 1.0) {
                        if (features[6] <= -0.5) {
                            if (features[5] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[8] <= -0.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[13] <= 0.5) {
                            if (features[6] <= -0.5) {
                                if (features[3] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 5; 
                                    classes[4] = 1; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 3; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 4; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 5; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[7] <= 1.5) {
                classes[0] = 0; 
                classes[1] = 5; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_10(float features[]) {
    int classes[5];
    
    if (features[0] <= 0.5) {
        if (features[3] <= 1.0) {
            classes[0] = 16; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[4] <= 0.0) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 1; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[1] <= 3.5) {
            if (features[13] <= 0.0) {
                if (features[11] <= 1.0) {
                    if (features[7] <= 1.0) {
                        if (features[4] <= -0.5) {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 8; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[3] <= 2.0) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 10; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 1; 
                                    classes[3] = 4; 
                                    classes[4] = 1; 
                                }
                            }
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[2] <= 0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[4] <= -0.5) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 1.5) {
                if (features[3] <= 3.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                    classes[4] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 3; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_11(float features[]) {
    int classes[5];
    
    if (features[13] <= 0.0) {
        if (features[4] <= 0.5) {
            if (features[2] <= 0.5) {
                if (features[7] <= 1.0) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[4] <= -0.5) {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 10; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 5; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 4; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
                classes[4] = 0; 
            } else {
                if (features[11] <= 1.0) {
                    if (features[5] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    } else {
        if (features[3] <= 2.0) {
            classes[0] = 26; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[5] <= 1.0) {
                if (features[1] <= 3.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_12(float features[]) {
    int classes[5];
    
    if (features[9] <= 3.5) {
        if (features[3] <= 2.0) {
            if (features[5] <= 1.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 16; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[13] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 1; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[13] <= 1.0) {
                if (features[2] <= 0.5) {
                    if (features[1] <= 3.5) {
                        if (features[7] <= 1.0) {
                            if (features[4] <= -0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 7; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 4; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[8] <= -0.5) {
                        if (features[7] <= 1.0) {
                            if (features[3] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 5; 
                                classes[4] = 2; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 1; 
                        }
                    } else {
                        if (features[7] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 3; 
                        }
                    }
                }
            } else {
                if (features[5] <= 1.0) {
                    if (features[13] <= 3.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 2; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 8; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    } else {
        classes[0] = 0; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 5; 
        classes[4] = 0; 
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_13(float features[]) {
    int classes[5];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
    } else {
        if (features[8] <= 0.5) {
            if (features[0] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[7] <= 1.0) {
                    if (features[5] <= 1.0) {
                        if (features[12] <= -0.5) {
                            if (features[1] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                if (features[1] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 8; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            if (features[13] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 2; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            if (features[13] <= 0.5) {
                                if (features[1] <= 2.0) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 9; 
                                    classes[4] = 1; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    }
                } else {
                    if (features[1] <= 3.5) {
                        if (features[10] <= -0.5) {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 5; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 3; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 1; 
                    }
                }
            }
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 5; 
            classes[4] = 0; 
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_14(float features[]) {
    int classes[5];
    
    if (features[2] <= -0.5) {
        classes[0] = 17; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
    } else {
        if (features[4] <= -0.5) {
            if (features[1] <= 2.0) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 3; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            } else {
                if (features[1] <= 3.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[13] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 4; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[13] <= 1.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        } else {
            if (features[5] <= 3.5) {
                if (features[6] <= -0.5) {
                    if (features[13] <= 0.5) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 10; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[3] <= 2.0) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                if (features[3] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 3; 
                                    classes[4] = 2; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                }
                            }
                        }
                    } else {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[13] <= 2.5) {
                                if (features[2] <= 0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_15(float features[]) {
    int classes[5];
    
    if (features[13] <= 0.0) {
        if (features[6] <= 0.5) {
            if (features[5] <= 3.5) {
                if (features[7] <= 1.0) {
                    if (features[5] <= 1.0) {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 3; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        }
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 5; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                if (features[3] <= 3.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 3; 
                                    classes[3] = 3; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 0; 
                                    classes[3] = 1; 
                                    classes[4] = 0; 
                                }
                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.5) {
                        if (features[9] <= 1.0) {
                            if (features[4] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 4; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 2; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 2; 
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 6; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 1; 
            }
        }
    } else {
        if (features[5] <= 1.0) {
            if (features[3] <= 2.0) {
                classes[0] = 17; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[13] <= 3.5) {
                    if (features[0] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[1] <= 2.0) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 1; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 1; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_16(float features[]) {
    int classes[5];
    
    if (features[2] <= -0.5) {
        classes[0] = 9; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
    } else {
        if (features[12] <= -0.5) {
            if (features[6] <= -0.5) {
                if (features[5] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[1] <= 3.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        if (features[3] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 7; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[1] <= 2.0) {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[1] <= 3.5) {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 3; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 1; 
                                classes[4] = 0; 
                            }
                        }
                    }
                }
            } else {
                if (features[5] <= 3.5) {
                    if (features[9] <= 1.0) {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 5; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 2; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 4; 
                    }
                }
            }
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 5; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    if (features[1] <= 2.0) {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_17(float features[]) {
    int classes[5];
    
    if (features[2] <= -0.5) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
    } else {
        if (features[2] <= 0.5) {
            if (features[7] <= 3.5) {
                if (features[0] <= 0.5) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[12] <= 0.5) {
                        if (features[13] <= 0.5) {
                            if (features[1] <= 3.5) {
                                if (features[5] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 1; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 2; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 18; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 4; 
                classes[4] = 0; 
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[12] <= -0.5) {
                    if (features[3] <= 2.0) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 5; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 7; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[1] <= 2.0) {
                        if (features[4] <= -0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 2; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[3] <= 3.5) {
                    if (features[4] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 4; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 1; 
                }
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_18(float features[]) {
    int classes[5];
    
    if (features[3] <= 0.0) {
        classes[0] = 14; 
        classes[1] = 0; 
        classes[2] = 0; 
        classes[3] = 0; 
        classes[4] = 0; 
    } else {
        if (features[8] <= -0.5) {
            if (features[12] <= -0.5) {
                if (features[1] <= 3.5) {
                    if (features[6] <= -0.5) {
                        if (features[3] <= 2.0) {
                            if (features[2] <= 0.5) {
                                classes[0] = 0; 
                                classes[1] = 1; 
                                classes[2] = 0; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                if (features[4] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 3; 
                                    classes[2] = 0; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            }
                        } else {
                            if (features[2] <= 0.5) {
                                if (features[5] <= 1.0) {
                                    classes[0] = 0; 
                                    classes[1] = 2; 
                                    classes[2] = 5; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 7; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 0; 
                                classes[3] = 2; 
                                classes[4] = 0; 
                            }
                        }
                    } else {
                        if (features[4] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 1; 
                        }
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 4; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[3] <= 2.0) {
                    classes[0] = 6; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[4] <= -0.5) {
                        if (features[0] <= 0.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 11; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[2] <= 0.5) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 3; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                }
            }
        } else {
            if (features[1] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 2; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 4; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

static int predict_out_num_props_19(float features[]) {
    int classes[5];
    
    if (features[0] <= 0.5) {
        if (features[6] <= 0.0) {
            classes[0] = 11; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 2; 
            classes[4] = 0; 
        }
    } else {
        if (features[13] <= 2.5) {
            if (features[8] <= -0.5) {
                if (features[2] <= 0.5) {
                    if (features[12] <= -0.5) {
                        if (features[1] <= 3.5) {
                            if (features[5] <= 1.0) {
                                classes[0] = 0; 
                                classes[1] = 3; 
                                classes[2] = 10; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 6; 
                                classes[3] = 0; 
                                classes[4] = 0; 
                            }
                        } else {
                            classes[0] = 0; 
                            classes[1] = 0; 
                            classes[2] = 1; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    } else {
                        if (features[13] <= 1.5) {
                            classes[0] = 1; 
                            classes[1] = 0; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        }
                    }
                } else {
                    if (features[3] <= 3.5) {
                        if (features[5] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 1; 
                            classes[2] = 0; 
                            classes[3] = 0; 
                            classes[4] = 0; 
                        } else {
                            if (features[4] <= 0.5) {
                                if (features[12] <= -0.5) {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 4; 
                                    classes[3] = 3; 
                                    classes[4] = 1; 
                                } else {
                                    classes[0] = 0; 
                                    classes[1] = 0; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
                                    classes[4] = 0; 
                                }
                            } else {
                                classes[0] = 0; 
                                classes[1] = 0; 
                                classes[2] = 1; 
                                classes[3] = 0; 
                                classes[4] = 3; 
                            }
                        }
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 2; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[6] <= 0.5) {
                    if (features[5] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 1; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 2; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 13; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            }
        }
    }
    int class_idx = 0;
    int class_val = classes[0];
    int i;
    for (i = 1; i < 5; i++) {
        if (classes[i] > class_val) {
            class_idx = i;
            class_val = classes[i];
        }
    }
    return class_idx;
}

int predict_out_num_props (float features[]) {
    int n_classes = 5;
    int classes[n_classes];
    int i;
    for (i = 0; i < n_classes; i++) {
        classes[i] = 0;
    }

    classes[predict_out_num_props_0(features)]++;
    classes[predict_out_num_props_1(features)]++;
    classes[predict_out_num_props_2(features)]++;
    classes[predict_out_num_props_3(features)]++;
    classes[predict_out_num_props_4(features)]++;
    classes[predict_out_num_props_5(features)]++;
    classes[predict_out_num_props_6(features)]++;
    classes[predict_out_num_props_7(features)]++;
    classes[predict_out_num_props_8(features)]++;
    classes[predict_out_num_props_9(features)]++;
    classes[predict_out_num_props_10(features)]++;
    classes[predict_out_num_props_11(features)]++;
    classes[predict_out_num_props_12(features)]++;
    classes[predict_out_num_props_13(features)]++;
    classes[predict_out_num_props_14(features)]++;
    classes[predict_out_num_props_15(features)]++;
    classes[predict_out_num_props_16(features)]++;
    classes[predict_out_num_props_17(features)]++;
    classes[predict_out_num_props_18(features)]++;
    classes[predict_out_num_props_19(features)]++;

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
                                    classes[0] = 0; 
                                    classes[1] = 1; 
                                    classes[2] = 2; 
                                    classes[3] = 0; 
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
            if (features[3] <= 3.5) {
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
                                    classes[0] = 0; 
                                    classes[1] = 2; 
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
                        classes[0] = 3; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 5; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                } else {
                    if (features[11] <= 1.0) {
                        if (features[9] <= 1.0) {
                            classes[0] = 0; 
                            classes[1] = 2; 
                            classes[2] = 0; 
                            classes[3] = 2; 
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
            }
        } else {
            if (features[9] <= 3.5) {
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
                if (features[5] <= 1.0) {
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
