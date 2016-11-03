import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import 'rxjs/add/operator/map';
import { routing } from './app.routing';

import { MaterialModule } from '@angular/material';

import { AppComponent } from './app.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { SubmissionComponent } from './submission/submission.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { UserComponent } from './user/user.component';
import { CritiqueComponent } from './critique/critique.component';
import { CritiqueFormComponent } from './critique/critique-form/critique-form.component';

@NgModule({
  declarations: [
    AppComponent,
    AssignmentComponent,
    AssignmentListComponent,
    DashboardComponent,
    SubmissionComponent,
    SubmissionListComponent,
    UserComponent,
    CritiqueComponent,
    CritiqueFormComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    ReactiveFormsModule,
    HttpModule,
    routing,
    MaterialModule.forRoot()
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }