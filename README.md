# Battaglia Navale

#### *Puntatori anarchici*

## 1. How to Compile:

**While you are in the main directory (battaglia-navale)**

- Launch `cmake . -B <cmake-folder-name>`. This will create the cmake configuration folder. Note: this can't be
  named `bin`
- Run `cmake --build <cmake-folder-name>`. This will create a `bin` folder and will build the actual executable

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
└───<cmake-folder-name>
│   │    <cmake configuration files>
│
└───bin
│   │   <executables>
│   
```

---

## 2. How to run the programs

After following the instructions in "How to compile" you can run `battaglia_navale` and `replay`. To do so just run these commands in the main folder of the project
```
./bin/battaglia_navale [pc|cc] <n value>

./bin/replay [v|f] [path/to/input_file.txt] <path/to/output_file.txt>
```

We added an optional n flag to customize the max amount of turns in a game. This is because with the default value (150) a game can be won between human and computer, but 2 computers almost always draw. We decided not to set an higher default value for computer vs computer games to make match/replay testing easier (finishing a replay is faster)

## 3. Designer Notes

### 3.1. GIT

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

### 3.2 Log File

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

### 3.3 Boards

We decided to implement in each board two function members: get_all and get_all_raw. They return all positions saved inside the grid without worrying about the ADT used below.

#### 3.3.1 Attackboard

Instead of creating a 12x12 bidimensional array we decided to implement the grid with a standard map.

This allowed us to access cells directly with the coordinate without parsing it every time.

In this case iterators were such an easy way to interact with data.

#### 3.3.2 Defenseboard

Instead of using a 12x12 matrix (bidimensional array) we decided to implement the grid with a vector of unique pointers to `Ship`.

This allowed us to avoid doing a O(n^2) search on the matrix to find a Ship, and instead allowed us to do a O(n) search on the vector of smart pointers to work with Ships.

Since we have a vector of smart pointers **move and copy constructors** are **disabled**. In the future if they will be needed they can just be re-enabled and a deep copy can be implemented.