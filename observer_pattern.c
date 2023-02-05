#include <stdio.h>

#define MAX_NO_OF_OBSERVERS 10u

/* Subject */
typedef struct{
	int lightLevel;
	int fogLevel;
	int rainLevel;
} t_lightingData;

typedef void(*pFnctPtrObserver)(const t_lightingData lightingData);

/* Observers list keeping */
static pFnctPtrObserver observerList[MAX_NO_OF_OBSERVERS] = {NULL};

/* Observer 1 */
static void updateHeadLights(const t_lightingData newLightingData) 
{
	if(newLightingData.lightLevel > 50u) {
		printf("Headlights turned on\n");
	} else {
	    printf("Headlights turned off\n");
	}
}

/* Observer 2 */
static void updateFogLights(const t_lightingData newLightingData) 
{
	if(newLightingData.fogLevel > 50u) {
		printf("Fog lights turned on\n");
	} else {
	    printf("Fog lights turned off\n");
	}
}

/* Observer 3 */
static void updateRainSensors(const t_lightingData newLightingData) 
{
	if(newLightingData.rainLevel > 50u) {
		printf("Rain sensors turned on\n");
	} else {
	    printf("Rain sensors turned off\n");
	}
}

/* Function to notify observers */
static t_lightingData lightingData = { .lightLevel = 0u, .fogLevel = 0u, .rainLevel = 0u };
static void notifyLightingData(void)
{
	for(int i = 0u; i < MAX_NO_OF_OBSERVERS; i++) {
		if(observerList[i] != NULL) {
			observerList[i](lightingData);
		}
	}
}

/* Function to update the data and call notify_lighting_data */
static void updateLightingData(t_lightingData newLightingData)
{
	/* Update lighting data */
	lightingData = newLightingData;
	
	/* Notify the registered observers */
	notifyLightingData();
}

/* Function to register a pointer to a function to observer_list */
static void registerObserver(const pFnctPtrObserver pObserverFcnt) 
{
	int obsIdx = 0u;
	while((observerList[obsIdx] != NULL) && (obsIdx < MAX_NO_OF_OBSERVERS)) {
		obsIdx++;
	}
	printf("Registering Observer %d\n", obsIdx+1u);
	observerList[obsIdx] = pObserverFcnt;
}

/* Function to deregister a pointer to a function from observer_list */
static void deRegisterObserver(const pFnctPtrObserver pObserverFcnt)
{
    for (int obsIdx = 0u; obsIdx < MAX_NO_OF_OBSERVERS; obsIdx++) {
        if (observerList[obsIdx] == pObserverFcnt) {
			printf("Deregistering Observer %d\n", obsIdx+1u);
            observerList[obsIdx] = NULL;
            break;
        }
    }
}

/* usage */
int main(void)
{
	/* Register observers */
	registerObserver(updateHeadLights);
	registerObserver(updateFogLights);
	registerObserver(updateRainSensors);
		
	/* Update with new data */
	const t_lightingData newLightingData = { .lightLevel = 60u, .fogLevel = 70u, .rainLevel = 80u };
	updateLightingData(newLightingData);
	
	/* Deregister observers */
	deRegisterObserver(updateHeadLights);
	deRegisterObserver(updateFogLights);
	deRegisterObserver(updateRainSensors);
	
	return 0;
}