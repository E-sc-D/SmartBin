#include "UserDetectorTask.h"

UserDetectorTask::UserDetectorTask(int pin){
    this->pin = pin;
    //arduino setup
}

void UserDetectorTask::tick(){
    //la svariable non gli serve
    //se il programma gira allora l'user c'è
    //altrimenti no
    //arduino controlla e in caso mette in sleep
}
