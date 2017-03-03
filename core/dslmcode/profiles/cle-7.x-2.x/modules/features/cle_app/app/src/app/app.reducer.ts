import { createSelector } from 'reselect';
import { ActionReducer } from '@ngrx/store';
import * as fromRouter from '@ngrx/router-store';
import { environment } from '../environments/environment';

/**
 * The compose function is one of our most handy tools. In basic terms, you give
 * it any number of functions and it returns a function. This new function
 * takes a value and chains it through every composed function, returning
 * the output.
 *
 * More: https://drboolean.gitbooks.io/mostly-adequate-guide/content/ch5.html
 */
import { compose } from '@ngrx/core/compose';

/**
 * storeFreeze prevents state from being mutated. When mutation occurs, an
 * exception will be thrown. This is useful during development mode to
 * ensure that none of the reducers accidentally mutates the state.
 */
import { storeFreeze } from 'ngrx-store-freeze';

/**
 * combineReducers is another useful metareducer that takes a map of reducer
 * functions and creates a new reducer that stores and gathers the values
 * of each reducer and stores them using the reducer's key. Think of it
 * almost like a database, where every reducer is a table in the db.
 *
 * More: https://egghead.io/lessons/javascript-redux-implementing-combinereducers-from-scratch
 */
import { combineReducers } from '@ngrx/store';

/**
 * Every reducer module's default export is the reducer function itself. In
 * addition, each module should export a type or interface that describes
 * the state of the reducer plus any selector functions. The `* as`
 * notation packages up all of the exports into a single object.
 */
import * as fromAssignment from './assignment/assignment.reducer';
import * as fromSubmission from './submission/submission.reducer';
import * as fromUser from './user/user.reducer';
import * as fromProject from './projects/project.reducer';
import * as fromImage from './image/image.reducer';
import * as fromActivityFeed from './activity-feed/activity-feed.reducer';

/**
 * Import types
 */
import { Submission } from './submission/submission';

/**
 * As mentioned, we treat each reducer like a table in a database. This means
 * our top level state interface is just a map of keys to inner state types.
 */
export interface State {
  assignments: fromAssignment.AssignmentState;
  submission: fromSubmission.SubmissionState;
  user: fromUser.UserState;
  projects: fromProject.ProjectState;
  image: fromImage.ImageState;
  router: fromRouter.RouterState;
  activityFeed: fromActivityFeed.ActivityFeedState;
}

/**
 * Because metareducers take a reducer function and return a new reducer,
 * we can use our compose helper to chain them together. Here we are
 * using combineReducers to make our top level reducer, and then
 * wrapping that in storeLogger. Remember that compose applies
 * the result from right to left.
 */
const reducers = {
  assignments: fromAssignment.reducer,
  submission: fromSubmission.submissionReducer,
  user: fromUser.reducer,
  projects: fromProject.projectReducer,
  image: fromImage.imageReducer,
  router: fromRouter.routerReducer,
  activityFeed: fromActivityFeed.activityFeedReducer
};

const developmentReducer: ActionReducer<State> = compose(storeFreeze, combineReducers)(reducers);
const productionReducer: ActionReducer<State> = combineReducers(reducers);

export function reducer(state: any, action: any) {
  if (environment.production) {
    return productionReducer(state, action);
  }
  else {
    return developmentReducer(state, action);
  }
}

/**
 * A selector function is a map function factory. We pass it parameters and it
 * returns a function that maps from the larger state tree into a smaller
 * piece of state. This selector simply selects the `books` state.
 *
 * Selectors are used with the `select` operator.
 *
 * ```ts
 * class MyComponent {
 * 	constructor(state$: Observable<State>) {
 * 	  this.booksState$ = state$.select(getBooksState);
 * 	}
 * }
 * ```
 */
export const getProjectState = (state:State) => state.projects;

/**
 * Every reducer module exports selector functions, however child reducers
 * have no knowledge of the overall state tree. To make them useable, we
 * need to make new selectors that wrap them.
 *
 * The createSelector function from the reselect library creates
 * very efficient selectors that are memoized and only recompute when arguments change.
 * The created selectors can also be composed together to select different
 * pieces of state.
 */
export const getProjects = createSelector(getProjectState, fromProject.getAll);
export const getProjectsCount = createSelector(getProjectState, fromProject.getCount);

/**
 * Assignments
 */
export const getAssignmentState = (state:State) => state.assignments;
export const getAssignments = createSelector(getAssignmentState, fromAssignment.getAll);
export const getAssignmentsLoading = createSelector(getAssignmentState, fromAssignment.getIsLoading);

/**
 * Users
 */
export const getUserState = (state:State) => state.user;
export const getUserPermissions = createSelector(getUserState, fromUser.getPermissions)
export const getUserToken = createSelector(getUserState, fromUser.getToken)
export const getMyUserUid = createSelector(getUserState, fromUser.getUid)

/**
 * Image
 */
export const getImageState = (state:State) => state.image;
export const getImageCurrentState = createSelector(getImageState, fromImage.getCurrentState);

/**
 * Submissons
 */
export const getSubmissionState = (state:State) => state.submission;
export const getAllSubmissions = createSelector(getSubmissionState, fromSubmission.getAll);
export const getSubmissionCurrentState = createSelector(getSubmissionState, fromSubmission.getCurrentState);
export const getMySubmissions = createSelector(getAllSubmissions, getMyUserUid, (submissions:Submission[], uid:number) => {
  return submissions.filter(s => s.uid === uid);
});
export const getSubmissionSavable = createSelector(getSubmissionCurrentState, getImageCurrentState, (s:fromSubmission.SubmissionStates, i:fromImage.ImageStates) => {
  return (s === fromSubmission.SubmissionStates.default && i === fromImage.ImageStates.default);
});

/**
 * Router
 */
export const getRouterState = (state:State) => state.router;

/**
 * Activity Feed
 */
export const getActivityFeedState = (state:State)  => state.activityFeed;
export const getActivityFeedCurrentState = createSelector(getActivityFeedState, fromActivityFeed.getCurrentState);