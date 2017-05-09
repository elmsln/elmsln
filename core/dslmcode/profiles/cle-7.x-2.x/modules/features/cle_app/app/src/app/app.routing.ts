import { ModuleWithProviders } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentFormComponent } from './assignment/assignment-form/assignment-form.component';
import { CritiqueComponent } from './critique/critique.component';
import { LoginComponent } from './login/login.component';
import { LogoutComponent } from './logout/logout.component';
import { ProjectsListComponent } from './projects/projects-list/projects-list.component';
import { AssignmentDialogComponent } from './assignment/assignment-dialog/assignment-dialog.component';
import { SubmissionComponent } from './submission/submission.component';
import { SubmissionCreateComponent } from './submission/submission-create/submission-create.component';
import { SubmissionDetailComponent } from './submission/submission-detail/submission-detail.component';
import { SubmissionEditComponent } from './submission/submission-edit/submission-edit.component';
import { SubmissionDialogComponent } from './submission/submission-dialog/submission-dialog.component';
import { SubmissionStatesComponent } from './submission/submission-states/submission-states.component';
import { SubmissionCritiqueComponent } from './submission/submission-critique/submission-critique.component';
import { DialogComponent } from './dialog/dialog.component';

const appRoutes: Routes = [
  {
    path: '',
    component: ProjectsListComponent
  },
  {
    path: 'projects',
    component: ProjectsListComponent
  },
  {
    path: 'assignments/:id',
    component: AssignmentComponent,
  },
  {
    path: 'assignment-create/:projectId',
    outlet: 'dialog',
    component: AssignmentDialogComponent
  },
  {
    path: 'assignment-edit/:assignmentId',
    outlet: 'dialog',
    component: AssignmentDialogComponent
  },
  {
    path: 'assignment-delete/:deleteAssignmentId',
    outlet: 'dialog',
    component: AssignmentDialogComponent
  },
  {
    path: 'submissions',
    children: [
      {
        path: 'create/:assignmentId',
        component: SubmissionCreateComponent
      },
      {
        path: ':submissionId',
        component: SubmissionComponent
      },
      {
        path: ':submissionId/edit',
        component: SubmissionEditComponent
      },
      {
        path: 'submission-states',
        component: SubmissionStatesComponent
      },
      {
        path: ':critiqueId',
        component: SubmissionCritiqueComponent
      }
    ]
  },
  {
    path: 'submissions/:submissionId/edit-state',
    outlet: 'dialog',
    component: SubmissionDialogComponent
  },
];

export const appRoutingProviders: any[] = [

];

export const routing: ModuleWithProviders = RouterModule.forRoot(appRoutes);
