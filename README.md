# Battaglia Navale

#### *Puntatori anarchici*

### 0. TODO

- [x] All DONE!

### 1. How to Compile:

**While you are in the main directory**

- Launch `cmake . -B <cmake-configuration-folder>`. This will create the cmake configuration folder. Note: this can't be
  named `bin`
- Run `cmake --build <cmake-configuration-folder>`. This will create a `bin` folder and will build the actual executable

At the end of the process you should be in a very similar situation

```
<Project Folder>
│   README.md
│   .gitignore
│   CMakeLists.txt    
|   statement.pdf
│
└───include
│   │   .h files and dirs
│
└───src
│   │   .cpp files and dirs
│   
└───<cmake-configuration-folder>
│   │    <cmake configuration files>
│
└───bin
│   │   <executables>
│   
```

---

### 2. Designer Notes

#### 2.1. GIT

We decided to use Git as dVCS and [GitHub](https://github.com/) as remote host. So we founded
an [organization](https://github.com/UniPD-PuntatoriAnarchici/) and created
a [repository](https://github.com/UniPD-PuntatoriAnarchici/battaglia-navale).

In order to keep development simpler and more straightforward, we decided to use one main branch (main) and one branch
per developer. For the same reason we also decided to use the following procedure:

- Pull from remote main branch.
- Switch to personal branch
- Merge/Rebase to align.
- Local development
- Add, commit
- Push to remote personal branch *(This is to have dual control and avoid a direct push to the master)*
- Pull request and merge request directly in the remote.

In this way we were able to maintain the linearity of the main branch without overlapping everyone's work.

![Network Graph](/res/NetworkGraph.png)

#### 2.2 Log File

Log file will be named as log-HC/CC-timestamp.txt where:

- CC is CpuPlayer vs CpuPlayer
- HC is HumanPlayer vs CpuPlayer

and will have the following format

```
HB8 HF10 VF2 HA3 HD7 HL7 HH11 HL2
HB8 HF10 VF2 HA3 HD7 HL7 HH11 HL2
2
F2 L2
L2 A1
F2 F10
```

Rows:

1. Player 1 ships in format ```OrientationRowColumn```
2. Player 2 ships in format ```OrientationRowColumn```
3. Starting player ```1 or 2 ```
4. to n. Players actions.

#### 2.3 Boards

We decided to implement in each board two method, get_all and get_all_raw, that allows to obtain all positions saved
inside
the grid without worry about the ADT used below.

##### 2.3.1 Attackboard

Instead of creating a 12x12 bidimensional array we decided to implement the grid with a standard map.

This allowed us to access cells directly with the coordinate without parsing it every time.

In this case iterators were such an easy way to interact with data.
