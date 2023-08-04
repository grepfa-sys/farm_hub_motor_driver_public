# ModBus Memory Map
| Coil | Use       | Function | 0           | 1           |
|------|-----------|----------|-------------|-------------|
| 00   | ON/OFF    | 1, 5, 15 | 0 - Off     | 1 - ON      |
| 01   | Direction | 1, 5, 15 | 0 - Forward | 1 - Reverse |

| Regi | Use            | Function | Value                 |
|------|----------------|----------|-----------------------|
| 0    | Movement Delta | 3, 6, 16 | 0 - None, >0 - Second |

# Segment Display Info

```
 --   --   -- 
|  | |  | |  |
 --   --   -- 
|  | |  | |  |
 --   --   -- 
```

## System
### Loading
기기 준비중인 상태
```


 --   --   -- 

    .    .
```
 

## Manual Mode
현장의 컨트롤 박스의 스위치로 제어를 했을때 
### Forward On
```
           -- 
          |  |
 --   --   -- 
|  | |  | |   
    . --      
```
m.oP

### Reverse On
```
      --      
     |    |   
 --           
|  | |    |  
    . --   -- 
```
m.CL

### Stop
```
      --      
     |    |   
 --   --   -- 
|  |    | |   
    . --   -- 
```
m.St

## Auto Mode
원격으로 제어를 했을때
### Forward On
```
 --        -- 
|  |      |  |
 --   --   -- 
|  | |  | |   
    . --      
```
A.oP

### Reverse On
```
 --   --      
|  | |    |   
 --           
|  | |    |  
    . --   -- 
```
A.CL

### Stop
```
 --   --      
|  | |    |   
 --   --   -- 
|  |    | |   
    . --   -- 
```
A.St