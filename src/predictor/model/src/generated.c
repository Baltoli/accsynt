#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int predict_out_num_props_0(float features[]) {
    int classes[5];
    
    if (features[13] <= 0.0) {
        if (features[5] <= 3.5) {
            if (features[9] <= 1.0) {
                if (features[3] <= 3.5) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 15; 
                        classes[3] = 0; 
                        classes[4] = 1; 
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
            if (features[1] <= 3.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 5; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 3; 
            }
        }
    } else {
        if (features[3] <= 2.0) {
            classes[0] = 20; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[0] <= 0.5) {
                classes[0] = 1; 
                classes[1] = 0; 
                classes[2] = 0; 
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
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 16; 
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

int predict_out_num_props_1(float features[]) {
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
                        classes[0] = 1; 
                        classes[1] = 4; 
                        classes[2] = 20; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 5; 
                        classes[3] = 3; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 3.5) {
                        classes[0] = 5; 
                        classes[1] = 7; 
                        classes[2] = 1; 
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
                if (features[10] <= -0.5) {
                    if (features[9] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 4; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 1; 
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
        if (features[6] <= 0.5) {
            classes[0] = 0; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 1; 
        } else {
            if (features[2] <= 0.5) {
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

int predict_out_num_props_2(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 14; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[1] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 5; 
                        classes[3] = 4; 
                        classes[4] = 1; 
                    }
                }
            } else {
                if (features[2] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 2; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[8] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
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
        if (features[3] <= 2.0) {
            if (features[4] <= -0.5) {
                classes[0] = 18; 
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
            if (features[0] <= 0.5) {
                classes[0] = 2; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 0; 
                    classes[1] = 12; 
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

int predict_out_num_props_3(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 6; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[11] <= 1.0) {
                    if (features[7] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 3; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 2; 
                    }
                } else {
                    classes[0] = 0; 
                    classes[1] = 4; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[4] <= -0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 3; 
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

int predict_out_num_props_4(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 11; 
                        classes[3] = 2; 
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
        } else {
            if (features[9] <= 3.5) {
                if (features[8] <= -0.5) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
                        classes[3] = 0; 
                        classes[4] = 3; 
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
                classes[3] = 4; 
                classes[4] = 0; 
            }
        }
    } else {
        if (features[2] <= -0.5) {
            classes[0] = 14; 
            classes[1] = 0; 
            classes[2] = 0; 
            classes[3] = 0; 
            classes[4] = 0; 
        } else {
            if (features[1] <= 2.0) {
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
            } else {
                if (features[13] <= 3.5) {
                    if (features[4] <= -0.5) {
                        classes[0] = 3; 
                        classes[1] = 4; 
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
                    classes[0] = 0; 
                    classes[1] = 3; 
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

int predict_out_num_props_5(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 15; 
                        classes[2] = 7; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[7] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 15; 
                        classes[3] = 4; 
                        classes[4] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
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

int predict_out_num_props_6(float features[]) {
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
                if (features[7] <= 1.0) {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 6; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 10; 
                        classes[3] = 4; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[9] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 1; 
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
    } else {
        if (features[2] <= 0.5) {
            if (features[12] <= -0.5) {
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

int predict_out_num_props_7(float features[]) {
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
                if (features[2] <= -0.5) {
                    classes[0] = 9; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[12] <= 0.5) {
                        classes[0] = 1; 
                        classes[1] = 15; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        } else {
            if (features[7] <= 1.0) {
                if (features[12] <= -0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 7; 
                        classes[3] = 3; 
                        classes[4] = 2; 
                    }
                } else {
                    if (features[13] <= 2.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[1] <= 3.5) {
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
            if (features[9] <= 1.0) {
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

int predict_out_num_props_8(float features[]) {
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
                        classes[0] = 2; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
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
        if (features[6] <= -0.5) {
            if (features[2] <= 0.5) {
                if (features[13] <= 0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 5; 
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
                if (features[3] <= 2.0) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 4; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[12] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 5; 
                        classes[3] = 4; 
                        classes[4] = 4; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        } else {
            if (features[8] <= 0.5) {
                if (features[7] <= 3.5) {
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
                        classes[4] = 1; 
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

int predict_out_num_props_9(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 13; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 10; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[6] <= -0.5) {
                    if (features[3] <= 2.0) {
                        classes[0] = 2; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 3; 
                        classes[3] = 5; 
                        classes[4] = 1; 
                    }
                } else {
                    if (features[11] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 3; 
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

int predict_out_num_props_10(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 21; 
                        classes[3] = 4; 
                        classes[4] = 1; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
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
            } else {
                if (features[3] <= 2.0) {
                    if (features[4] <= -0.5) {
                        classes[0] = 5; 
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
                } else {
                    classes[0] = 0; 
                    classes[1] = 6; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                }
            }
        } else {
            if (features[6] <= -0.5) {
                if (features[12] <= -0.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 2; 
                    classes[4] = 0; 
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

int predict_out_num_props_11(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 17; 
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
                if (features[8] <= -0.5) {
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
            if (features[0] <= 0.5) {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 2; 
                classes[4] = 0; 
            } else {
                if (features[3] <= 3.5) {
                    if (features[9] <= 1.0) {
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
        if (features[1] <= 3.5) {
            if (features[4] <= -0.5) {
                if (features[3] <= 2.0) {
                    classes[0] = 26; 
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
                        classes[1] = 6; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 3; 
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

int predict_out_num_props_12(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 11; 
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
                    if (features[10] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 3; 
                        classes[3] = 6; 
                        classes[4] = 6; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
                if (features[0] <= 0.5) {
                    classes[0] = 2; 
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

int predict_out_num_props_13(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 11; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 10; 
                        classes[3] = 9; 
                        classes[4] = 1; 
                    }
                } else {
                    if (features[2] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 4; 
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

int predict_out_num_props_14(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 9; 
                        classes[2] = 7; 
                        classes[3] = 0; 
                        classes[4] = 0; 
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
            if (features[6] <= -0.5) {
                if (features[12] <= -0.5) {
                    if (features[1] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 16; 
                        classes[3] = 3; 
                        classes[4] = 2; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 0; 
                        classes[3] = 1; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 2.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 1; 
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

int predict_out_num_props_15(float features[]) {
    int classes[5];
    
    if (features[13] <= 0.0) {
        if (features[6] <= 0.5) {
            if (features[5] <= 3.5) {
                if (features[7] <= 1.0) {
                    if (features[5] <= 1.0) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 4; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 8; 
                        classes[3] = 4; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[10] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 5; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 2; 
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
        if (features[3] <= 2.0) {
            if (features[0] <= 0.5) {
                classes[0] = 11; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                if (features[5] <= 1.0) {
                    classes[0] = 6; 
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
        } else {
            if (features[2] <= 0.5) {
                if (features[0] <= 0.5) {
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
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 4; 
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

int predict_out_num_props_16(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 2; 
                        classes[2] = 9; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[3] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 10; 
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
            } else {
                if (features[3] <= 3.5) {
                    if (features[7] <= 3.5) {
                        classes[0] = 0; 
                        classes[1] = 7; 
                        classes[2] = 2; 
                        classes[3] = 0; 
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
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 4; 
                }
            }
        } else {
            if (features[2] <= 0.5) {
                if (features[1] <= 2.0) {
                    classes[0] = 3; 
                    classes[1] = 0; 
                    classes[2] = 0; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[1] <= 3.5) {
                        classes[0] = 5; 
                        classes[1] = 13; 
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
                classes[0] = 0; 
                classes[1] = 0; 
                classes[2] = 2; 
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

int predict_out_num_props_17(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 22; 
                        classes[2] = 5; 
                        classes[3] = 0; 
                        classes[4] = 0; 
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
            if (features[13] <= 0.5) {
                if (features[1] <= 2.0) {
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
                    if (features[6] <= -0.5) {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 1; 
                        classes[3] = 7; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 5; 
                    }
                }
            } else {
                if (features[13] <= 2.5) {
                    classes[0] = 0; 
                    classes[1] = 0; 
                    classes[2] = 2; 
                    classes[3] = 0; 
                    classes[4] = 0; 
                } else {
                    if (features[5] <= 1.0) {
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

int predict_out_num_props_18(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 6; 
                        classes[2] = 17; 
                        classes[3] = 2; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 1; 
                    }
                } else {
                    if (features[3] <= 3.5) {
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
                    if (features[13] <= 2.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 3; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 12; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            }
        } else {
            if (features[6] <= 0.5) {
                if (features[4] <= 0.5) {
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
                    classes[4] = 2; 
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

int predict_out_num_props_19(float features[]) {
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
                        classes[0] = 0; 
                        classes[1] = 3; 
                        classes[2] = 17; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    } else {
                        classes[0] = 1; 
                        classes[1] = 1; 
                        classes[2] = 0; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                } else {
                    if (features[13] <= 0.5) {
                        classes[0] = 0; 
                        classes[1] = 1; 
                        classes[2] = 5; 
                        classes[3] = 5; 
                        classes[4] = 4; 
                    } else {
                        classes[0] = 0; 
                        classes[1] = 0; 
                        classes[2] = 2; 
                        classes[3] = 0; 
                        classes[4] = 0; 
                    }
                }
            } else {
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
                    classes[4] = 3; 
                }
            }
        } else {
            if (features[3] <= 2.0) {
                classes[0] = 4; 
                classes[1] = 0; 
                classes[2] = 0; 
                classes[3] = 0; 
                classes[4] = 0; 
            } else {
                classes[0] = 0; 
                classes[1] = 13; 
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
