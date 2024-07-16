# What is libhsm?

**libhsm** is a Hierarchical State Machine engine library implemented in C. It is intended to provide a well-tested SM engine which can be used for simple as well as for more complicated state machines.

# Main features
- state hierarchy;
- history state support for composite states;
- event-based execution in a "run-to-completion" fashion;
- guard conditions evaluation for events;
- action handlers support for events;
- on entry/exit handlers for each state;
- integrated tracing of event handling and state transitions which can be used for SM debugging in real-time;
- Python-based code generator is available;
- PlantUML standard output support from the code generator to enable SM visualization;

# How do I describe my state machine?
As a matter of fact, you can manually write your state machine configuration in C. That could work for simple state machines but is anyway something you probably want to avoid. Generally you would opt for the **hsmgen.py** code generator but we will first have a very basic look into how a C SM configuration looks like just for completeness of this guide.

## Related C types
There are two types of states recognized by **libhsm**:
- Simple states (represented by `sState_t` structure instances)
  - Such states do not have nested states and are also called terminating or leaf states;
- Composite states (represented by `sCompositeState_t` structure instances)
  - These states can contain other nested states and are used to describe a state machine hierarchy;

In the terms above, a state machine in **libhsm** is always represented by a `sCompositeState_t` structure instance since this is the top level of the SM hieararchy and all other states live underneath that state.

In order to describe a full state machine, we need states and transitions between those states. Transitions in **libhsm** are described by `sTransition_t` structure instances.

### Example state machine
Here is an example state machine code which has only two states which can transition between each other:

```
#include "libhsm.h"
#include "Example_SM_config_user.h"


static const sTransition_t tran_stopped_ev_start_running;
static const sTransition_t tran_running_ev_stop_stopped;


static const sTransition_t* trans_stopped[] =
{
    &tran_stopped_ev_start_running,
    NULL
};

static const sTransition_t* trans_running[] =
{
    &tran_running_ev_stop_stopped,
    NULL
};


// Example_SM states forward declarations
static const sState_t state_stopped;
static const sState_t state_running;

// Example_SM root state definition
sCompositeState_t state_Example_SM =
{
    {
        // pName
        "state_Example_SM",
        // onEntryFunc
        NULL,
        // onExitFunc
        NULL,
        // pTransitionList
        NULL,
        // eType
        eHSM_StateType_Composite,
        // pParent
        NULL
    },
    // pInitialState
    HSM_UPCAST_STATE(&state_stopped),
    // pHistoryState
    HSM_UPCAST_STATE(&state_stopped),
    // pActiveState
    HSM_UPCAST_STATE(&state_Example_SM)
};

static const sState_t state_stopped =
{
    // pName
    "state_stopped",
    // onEntryFunc
    &Example_SM_on_entry_stopped,
    // onExitFunc
    &Example_SM_on_exit_stopped,
    // pTransitionList
    trans_stopped,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Example_SM)
};


static const sState_t state_running =
{
    // pName
    "state_running",
    // onEntryFunc
    &Example_SM_on_entry_running,
    // onExitFunc
    &Example_SM_on_exit_running,
    // pTransitionList
    trans_running,
    // eType
    eHSM_StateType_Simple,
    // pParent
    HSM_UPCAST_STATE(&state_Example_SM)
};

static const sTransition_t tran_stopped_ev_start_running =
{
    // event
    ev_Example_SM_start,
    // guard
    &Example_SM_guard_is_running_allowed,
    // target state
    HSM_UPCAST_STATE(&state_running),
    // action
    &Example_SM_action_prepare_run,
};

static const sTransition_t tran_running_ev_stop_stopped =
{
    // event
    ev_Example_SM_stop,
    // guard
    NULL,
    // target state
    HSM_UPCAST_STATE(&state_stopped),
    // action
    NULL
};
```

Now you know why you should probably use the code generator to describe this. Anyway the definition should be straightforward:
- we have a root state which represents the whole SM --> `state_Example_SM`;
- it has an initial state `state_stopped` which is activated as soon as the SM receives the `eHSM_StdEvent_Reset` event;
- specific to the root state is that it doesn't have any transitions and also its parent pointer is set to `NULL` (end of hierarchy);
- the two SM states are described in a similar fashion but they are simple states;
- the transitions are grouped in linear `NULL`-terminated lists and each transition consists of:
  - an event which triggers it;
  - an optional guard condition function which gets executed when the event is fired to a state which supports it;
  - an optional action function which gets executed if the transition is performed;
  - a target state which becomes the active state when the transition is performed.

## Using YAML to describe the state machine
Instead of writing your HSM configuration in C by hand, you can use a more simpler description format to feed to **hsmgen.py** and produce the full code automatically. This chapter describes how you can describe your state machines in YAML. One YAML file may contain one or more state machine descriptions.

Let's see how the HSM from the previous section can be described in YAML:

```
Example_SM:                     # State machine name and top YAML node
    states:                     # indicates a list of states
        - stopped:              # name of a state
            transitions:        # start of the transition list for "stopped" state
                - running:      # name of a target state
                    - { event: start, guard: is_running_allowed, action: prepare_run }  # transition description
        - running:              # name of a state
            transitions:        # start of the transition list for "running" state
                - stopped:      # name of a target state
                    - event: stop   # transition description
    attributes:                 # named attributes applicable to composite states
        initial: stopped
```

`Example_SM` is the top node of the YAML document and it specifies the name of the SM. If you remember, we mentioned that each SM in **libhsm** is actually represented by a Composite state. This implies that the same format is used to describe any other state in the state machine. The `states` section contains a list of the nested states of this state machine - in this case: `stopped` and `running`. States can have attributes which are named key-value pairs.

The following attributes are supported by the generator:
- `initial` - used to specify the name of the initial state for a composite state. That state will be activated when a transition to the Composite state is performed; the attribute is taken into account only for composite states;
- `on_entry` - specifies whether an <code>on_entry</code> handler is generated for the state where this attribute is specified; valid values are [True, False]; if the attribute is not explicitly specified, its assumed value is **True**;
- `on_exit` - specifies whether `on_exit` handler is generated.

Simple transitions specify only an event which triggers the transition, e.g.:
```
transitions:
    - event: stop
```
If you need to specify more parameters of a transition, you have to use a slightly different notation, i.e.:
```
transitions:
    - { event: stop, guard: is_stop_allowed, action: on_stop_action }
```

### Special keywords supported
- `__auto` - accepted by the `guard` and `action` arguments of a transition definition when you don't want to specify a particular name for the guard or action function and you would like to rely on automatic name generation for those handlers;
- `__periodic` - can be used as an event name and represents a standard periodic event denoted by the `eHSM_StdEvent_Periodic` enum value in the C code; this event is always available and you don't have to define it yourself; it is used to model continuous state processing activities;
- `__history_<state name>` - can be used as a state name under the `transitions` section; it applies only for Composite states and represents the last active substate of the Composite as a target state of a transition, e.g.

```
Example_SM:
    states:
        - stopped:
            transitions:
                - __history_Processing:     # relates to the last active substate of the Processing composite state
                    - event: go_back
```
- `__self` - can be used as a state name under the `transitions` section; it is used to model a pseudo-transition to the same state but without triggering the on_entry/on_exit handlers of the state;

## Running the hsmgen.py code generator
Use `hsmgen.py --help` to get a list of options.

*Example:*
`hsmgen.py --conf my_hsm.yaml --outpath .\my_hsm_gen`

This will use the description provided in `my_hsm.yaml` file and generate the state machine C code in the specified output path folder. In addition to that, a PlantUML description of the HSM will also be provided as a `.plantuml` file which you can render to visualize the state machine [PlantUML](https://plantuml.com/).

## Generated files
| File name                 | Description                                                                                                                                              | Shall be edited by user |
| ------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------- |
| `<sm_name>_config.c`      | State machine descriptor code                                                                                                                            | No                      |
| `<sm_name>_sm_user.h`     | Header file containing user-defined events and SM instance symbol definition                                                                             | No                      |
| `<sm_name>_config_user.c` | This file contains the defintions of all guard and action handlers. It is the only file you have to modify in order to implement your SM custom behavior | Yes                     |
| `<sm_name>_config_user.h` | Header file with the prototypes of state entry/exit, guard and action handlers as well as user-defined events                                            | No                      |

## I generated my SM code. How do I use it?

If you finished generating the code for your SM, you can go for the actual integration and writing of your SM handlers body. Edit your `<sm_name>_config_user.c` file to provide your custom behavior. As you will probably notice, there are special comment tags for each generated handler:
```
// GEN_OBJ_START::Test_SM_on_entry_Initial
void Test_SM_on_entry_Initial(sState_t * const pSMRoot, const sHSM_EventType_t * const pEvent)
{
    // USER_CODE_START::onEntry_Initial

    env.on_entry_Initial_cnt++;

    // USER_CODE_END::onEntry_Initial
}
// GEN_OBJ_END::Test_SM_on_entry_Initial
```

Pay attention to not delete or change the content of those tags because those enable automatic code merge if you happen to update your YAML file and re-generate your SM code. During that process, all *"do not edit"* files above will be replaced but the `<sm_name>_config_user.c` file will be merged preserving all manually written code you already provided. If you deleted a handler in your new version of the YAML file, the removed code will be preserved at the end of the `.c` file inside comments for your reference so you can still use it by copying if needed.

Now you can try firing some events to your SM. Start by including `<sm_name>_user.h` header which contains all custom user events you defined in your YAML description. This header will also pull-in `libhsm.h` which provides the HSM APIs. You should be able to find the SM instance object name from the `<sm_name>_user.h` file as `<sm_name>_instance`. Use this name with the HSM APIs to fire events to the SM or query the current state.

```
#include "<sm_name>_user.h"

int main()
{
    // reset your SM...
    bool res = HSM_TriggerEvent(<sm_name>_instance, eHSM_StdEvent_Reset);

    if (res)
    {

    }
    else
    {
        // oh, no! Could not reset the SM for some reason... :/
    }
}
```

Please note that all entry/exit, guard and action handlers shall not implement blocking behavior because they are executed in the context of the `HSM_TriggerEvent()` call. If you block inside those functions, your SM will not be able to move forward and change state as requested. Any blocking behavior shall be separated in their own thread and checking of status shall be performed via `__periodic` events fired regularly to the SM in order to keep the SM responsive to other events.

## SM Integration Hints
If you integrate a single-instance SM in a multi-threaded environment or you want to support firing of events in interrupts, you must implement an event queue for your state machine which is processed in a separate task to avoid re-entrancy issues and corruption of state.

## FAQ

### I can write state machines easily without using an engine. What benefits do I have if I rely on **libhsm**?
In fact, for simple state machines, you may be well off writing your own code for the SM logic. That would usually be simple enough to maintain and it may not be as difficult to debug and fix issues. However, imagine a state machine where you have many states which are arranged in a hierarchy. This is where you would really benefit if using an SM engine. The engine comes pretested and ensures that your handlers get executed on the proper events fired. You can concentrate on application logic rather than debugging state machine logic. Hierarchical state machine logic is way more complicated than simple state machine logic and it may require a lot of testing to make right.
Another situation where the use of an SM engine is beneficial is when you have to edit your state machine transition behavior. As this implementation would be decoupled from your application logic, you can easily change your SM description and generate the code again without even touching your application code. The room for error and regressions is smaller since you change only what is really necessary.
Last but not least, the engine provides a standardized trace macros which can be replaced by the user. This way you can monitor your SM execution by redirecting the **libhsm** trace output to a serial console or a file. That could even be interfaced to a graphical SM debugger.

### I want to change the state of my SM. Why isn't there any APIs for that?
There is an API for that and it is called `HSM_TriggerEvent()`. You can change your SM state by firing the correct events which can get you in that state by following the SM graph. This is what the behavior would be in the actual code. If you need shortcuts, then it means you need a different state machine which supports different kinds of transitions. In fact, direct changing the state of an SM may seem like a good idea at first but for complicated SMs where there is hierarchy and history states must be maintained, this may cause quite a lot of trouble. For that reason, **libhsm** only supports a standard reset event which puts you in the initial SM state but switching to arbitrary states is not provided as an option since it has to happen by following the SM transition logic to ensure correct behavior at all times.

### YAML description is easy enough but it would be better if I can see my state machine to easily determine issues with its description. Can I do that?
Yes, indeed. When you create a basic YAML description, you can run `hsmgen.py` to make a quick code generation. Along with the C code, you will also get a PlantUML file which can be rendered to visualize the SM you described. Check [PlantUML](https://plantuml.com/) reference for more details.

### I have a feature request or a bug report. How to communicate that and to whom?
Please create a Jira ticket [here](https://endurosat.atlassian.net/jira/software/c/projects/SPE/issues) and set the Jira `Component` field to `libhsm`.