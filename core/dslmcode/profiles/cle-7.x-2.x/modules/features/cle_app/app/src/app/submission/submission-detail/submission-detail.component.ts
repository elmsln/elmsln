import { Component, OnInit, Input, AfterViewInit } from '@angular/core';
import { ActivatedRoute, Router, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { loadSubmissions } from '../submission.actions';
import { Submission } from '../submission';
import { ElmslnService } from '../../elmsln.service';

@Component({
  selector: 'app-submission-detail',
  templateUrl: './submission-detail.component.html',
  styleUrls: ['./submission-detail.component.css']
})
export class SubmissionDetailComponent implements OnInit, AfterViewInit {
  @Input() submission:Submission;

  constructor(
    private elmslnService:ElmslnService
  ) { 
  }

  ngOnInit() {
  }

  ngAfterViewInit() {
    this.elmslnService.exportLifecycleHook('submissionDetailComponentInit');
  }
}