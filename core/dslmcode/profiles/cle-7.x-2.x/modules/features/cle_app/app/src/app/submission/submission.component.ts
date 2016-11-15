import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Params } from '@angular/router';
import { Location } from '@angular/common';
import { SubmissionService } from '../submission.service';
import { CritiqueFormComponent } from '../critique/critique-form/critique-form.component';
import { CritiqueListComponent } from '../critique/critique-list/critique-list.component';

import { MdTabGroup, MdTab } from '@angular/material';

@Component({
  selector: 'cle-submission',
  templateUrl: './submission.component.html',
  styleUrls: ['./submission.component.css'],
  providers: [SubmissionService, CritiqueListComponent],
})
export class SubmissionComponent implements OnInit {
  /**
   * Variables
   */
  submissionId: number;
  submission: any;
  author: any;
  activeTabIndex: number = 1;

  constructor(
    private route: ActivatedRoute,
    private location: Location,
    private submissionService: SubmissionService
  ) { }

  ngOnInit() {
    // get the submission id from the route parameters
    this.route.params.forEach((params: Params) => {
      let id = +params['id'];
      this.submissionId = id;
    });

    // load the submission
    if (this.submissionId) {
      this.submissionService.getSubmission(this.submissionId)
        .subscribe(data => {
          this.submission = data;
        });
    }
  }

  /**
   * Events
   */
  // when a critique is submitted, we are going to
  // switch the tab back to All Feedback
  critiqueCreated(critique) {
    this.activeTabIndex = 0;
  }

  // when the user clicks a tab, update the tab index
  // that we are keeping track of.
  tabChange(event) {
    this.activeTabIndex = event.index;
  }
}
