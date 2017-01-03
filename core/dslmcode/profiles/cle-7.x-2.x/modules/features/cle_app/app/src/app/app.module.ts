import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { routing } from './app.routing';
import { StoreModule } from '@ngrx/store';
import { StoreDevtoolsModule } from '@ngrx/store-devtools';
import { EffectsModule } from '@ngrx/effects';

// reducers
import { reducer as assignmentReducer } from './reducers/assignments';
import { reducer as userReducer } from './reducers/users';
import { submissionReducer } from './submission/submission.reducer';
// effects
import { AppEffects } from './app.effects';
import { SubmissionEffects } from './submission/submission.effects';
// services
import { ElmslnService } from './elmsln.service';
import { CritiqueService } from './critique.service';
import { AssignmentService } from './assignment.service';
import { SubmissionService } from './submission/submission.service';
// Moment.js
import { MomentModule } from 'angular2-moment';
// components
import { AppComponent } from './app.component';
import { AssignmentComponent } from './assignment/assignment.component';
import { AssignmentListComponent } from './assignment/assignment-list/assignment-list.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { UserComponent } from './user/user.component';
import { CritiqueComponent } from './critique/critique.component';
import { CritiqueFormComponent } from './critique/critique-form/critique-form.component';
import { LoginComponent } from './login/login.component';
import { LogoutComponent } from './logout/logout.component';
import { CritiqueListComponent } from './critique/critique-list/critique-list.component';
import { WysiwygjsComponent } from './wysiwygjs/wysiwygjs.component';
import { AssignmentFormComponent } from './assignment/assignment-form/assignment-form.component';
import { ProjectsComponent } from './projects/projects.component';
import { ProjectsListComponent } from './projects/projects-list/projects-list.component';
import { DropdownComponent } from './components/dropdown/dropdown.component';
import { ProjectCardComponent } from './projects/project-card/project-card.component';
import { ProjectItemComponent } from './projects/project-item/project-item.component';
import { EditableFieldComponent } from './editable-field/editable-field.component';
import { DatetimeInputComponent } from './datetime-input/datetime-input.component';
import { AssignmentDialogComponent } from './assignment/assignment-dialog/assignment-dialog.component';
import { SubmissionCreateComponent } from './submission/submission-create/submission-create.component';
import { SubmissionFormComponent } from './submission/submission-form/submission-form.component';
import { SubmissionListComponent } from './submission/submission-list/submission-list.component';
import { SubmissionDetailComponent } from './submission/submission-detail/submission-detail.component';
import { SubmissionComponent } from './submission/submission.component';

@NgModule({
  declarations: [
    AppComponent,
    AssignmentComponent,
    AssignmentListComponent,
    DashboardComponent,
    UserComponent,
    CritiqueComponent,
    CritiqueFormComponent,
    LoginComponent,
    LogoutComponent,
    CritiqueListComponent,
    WysiwygjsComponent,
    AssignmentFormComponent,
    ProjectsComponent,
    ProjectsListComponent,
    DropdownComponent,
    ProjectCardComponent,
    ProjectItemComponent,
    EditableFieldComponent,
    DatetimeInputComponent,
    AssignmentDialogComponent,
    SubmissionComponent,
    SubmissionCreateComponent,
    SubmissionFormComponent,
    SubmissionListComponent,
    SubmissionDetailComponent
  ],
  imports: [
    BrowserModule,
    HttpModule,
    routing,
    FormsModule,
    ReactiveFormsModule,
    MomentModule,
    StoreModule.provideStore({
      assignments: assignmentReducer,
      user: userReducer,
      submissions: submissionReducer
    }),
    EffectsModule.run(AppEffects),
    EffectsModule.run(SubmissionEffects),
    StoreDevtoolsModule.instrumentOnlyWithExtension()
  ],
  providers: [
    ElmslnService,
    CritiqueService,
    AssignmentService,
    SubmissionService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
