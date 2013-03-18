            if(_readyQueue[0].getIOBursts().size() > 0){
                sendExecutingProcessToIO();
            }  
            else {
                _readyQueue.erase(_readyQueue.begin());
            }
        }
    }
}
