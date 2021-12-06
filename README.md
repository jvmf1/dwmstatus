# installation
install [jvmf1/slib](https://github.com/jvmf1/slib)
```sh
git clone https://github.com/jvmf1/dwmstatus
cd dwmstatus
sudo make install
```
# config.h example
```c
Cell cells[] = {
	// will run "date" every 1000ms
	CELL("date", -1, 1000)
	
  	// the cell below will run as an separator
	CELL("echo ' | '", -1, -1)
	
  	// "backlight" will trigger on signal 34 (pkill -34 dwmstatus)
	CELL("backlight", 34, -1)
  
	CELL("echo ' | '", -1, -1)
  
	CELL("/home/user/myscipt.sh", -1, 1000)
};
```
