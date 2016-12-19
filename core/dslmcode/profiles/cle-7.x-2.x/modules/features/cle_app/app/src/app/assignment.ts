import { ActionReducer, Action } from '@ngrx/store';

export class Assignment {
  id:number = null;
  title:string = null;
  type:string = null;
  status:boolean = null;
  created:number = null;
  startDate:string = null;
  endDate:string = null;
  project:number = null;
  description:string = null;
}

export const ADD_ASSIGNMENTS = 'ADD_ASSIGNMENTS';
export const ADD_ASSIGNMENT = 'ADD_ASSIGNMENT';

export const assignments: ActionReducer<Assignment[]> = (state: Assignment[] = [], action: Action) => {
    switch (action.type) {
        case ADD_ASSIGNMENTS:
            return action.payload;
        case ADD_ASSIGNMENT:
            return [...state, action.payload];
        default:
            return state;
    }
}